#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#pragma once

#include <fstream>
#include <filesystem>
//#include <exception>
#include <optional>
#include <cstdint>
#include <array>
#include <utility>
#include <memory>

namespace fs = std::filesystem;

namespace file_handler {

    using Size = uint_fast64_t;
    using Index = uint_fast64_t;

    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, size_t size);
    } //namespace literals

    using namespace literals;
    
    void CreateFileSystemObject(const fs::path& path, bool create_recursively = false);

    fs::path MakeValidPath(fs::path&& path, bool create_recursively = false);
    fs::path MakeValidPath(std::string path, bool create_recursively = false);
    fs::path MakeValidPath(const char* path_obj, bool create_recursively = false);
    
    
    //Overload fstream operator<< for accepting arrays
    template <typename Data, size_t Capacity>
    std::fstream& operator<<(std::fstream& out, std::array<Data, Capacity> data) {
        for (const auto& d : data) {
            out << d;
        }
        
        return out;
    }

    template <typename T>
    class File {
    public:
        typedef T Type;

        enum class Mode : bool {
            TEXT,
            BINARY
        };
        
    public:
        File(Mode mode, fs::path default_extension) 
        : MODE_(mode)
        , DEFAULT_EXTENSION(std::move(default_extension)) {

        }

        File(Mode mode, fs::path default_extension, fs::path filename)
        : MODE_(mode)
        , DEFAULT_EXTENSION(std::move(default_extension))
        , filename_(std::move(filename))
        {
            ValidateExtension();
            CreateFileSystemObject(filename_);
            OpenFile();
            InitProps();
        }
        
        void SetFilename(fs::path filename) {
            filename_ = std::move(filename);
            ValidateExtension();
            CreateFileSystemObject(filename_);

            Reset(false);
        }

        const fs::path& GetFilename() const {
            return filename_;
        }

        Size GetSize() const {
            return this -> ToElementSize(this -> size_);
        }

        bool IsEmpty() const {
            return size_ == 0;
        }

        void Reset(bool trunc = true) {
            if (!file_) {
                file_.clear();
            }
            
            if (GetFile().is_open()) {
                file_.close();
            }

            OpenFile(trunc);
            InitProps();
        }

        Index Write(T* source
                         , Size count = 1
                         , std::optional<Index> index = std::nullopt) {

            if (count > 0) {
                if (!source) {
                    throw std::invalid_argument{"A nullptr was passed when calling File<T>::WriteData(...)"};
                }
                
                SetWriteIndex(index);
                GetFile().write(reinterpret_cast<char*>(source), ToByteSize(count));
                GetFile().flush();
                UpdateWriteIndexAndSize();
            }

            return ToElementSize(write_index_);
        }

        template <typename CompatibleType>
        Index PutInStream(const CompatibleType* source
                       , std::optional<Index> index = std::nullopt) {

            if (!source) {
                throw std::invalid_argument{"A nullptr was passed when calling File<T>::WriteData(...)"};
            }
            
            SetWriteIndex(index);
            GetFile() << *source;
            GetFile().flush();
            UpdateWriteIndexAndSize();

            return ToElementSize(write_index_);
        }

        virtual Index Read(T* target
                        , Size count = 1
                        , std::optional<Index> index = std::nullopt) {

            if (count > 0) {
                if (!target) {
                    throw std::invalid_argument{"A nullptr was passed when calling File<T>::ReadData(...)"};
                }
    
                const auto count_in_bytes = ToByteSize(count);

                SetReadIndex(index);

                if (!IsWithinRange(file_.tellg(), count_in_bytes)) {
                    throw std::out_of_range{"When calling File<T>::ReadData(...), the required amount of data to read exceeds the existent data"};
                }          
                
                GetFile().read(reinterpret_cast<char*>(target), count_in_bytes);
                UpdateReadIndex();
            }

            return ToElementSize(read_index_);
            
        }    
        
        template <typename CompatibleType>
        Index GetFromStream(CompatibleType* target
                          , std::optional<Index> index = std::nullopt) {

            if (!target) {
                throw std::invalid_argument{"A nullptr was passed when calling File<T>::ReadData(...)"};
            }

            SetReadIndex(index); 
            GetFile() >> *target;
            UpdateReadIndex();
            

            return ToElementSize(read_index_);
        }
    protected:
        virtual ~File() = default;

    private:
        void ValidateExtension() {
            if (!filename_.has_extension()) {
                filename_.replace_extension(DEFAULT_EXTENSION);
            }
        }

        std::fstream& GetFile() {
            
            if (!file_) {
                throw fs::filesystem_error {"Unexpected error, while attempting to use file.", std::make_error_code(std::errc::io_error)};
            } 

            return file_;
        }

        void OpenFile(bool trunc = false) {
            std::ios_base::openmode open_mode;

            if (trunc) {
                switch (MODE_) {
                    case Mode::TEXT:
                        open_mode = std::ios_base::trunc | std::ios_base::out | std::ios_base::in;
                        break;
                    case Mode::BINARY:
                        open_mode = std::ios_base::trunc | std::ios_base::out | std::ios_base::in | std::ios_base::binary;
                        break;
                }
            } else {
                switch (MODE_) {
                    case Mode::TEXT:
                        open_mode = std::ios_base::out | std::ios_base::in;
                        break;
                    case Mode::BINARY:
                        open_mode = std::ios_base::out | std::ios_base::in | std::ios_base::binary;
                        break;
                }
            }

            GetFile().open(filename_, open_mode);
        }

        void InitProps() {
            file_.seekp(0, std::ios::end);
            write_index_ = file_.tellp();
            size_ = write_index_;

            file_.seekg(0, std::ios::beg);
            read_index_ = file_.tellg(); 
        }
  
    private:
        Size ToByteSize(Size num_of_items) const {
            return static_cast<Size>(num_of_items * sizeof(T));
        }

        Size ToElementSize(Size num_of_bytes) const {
            return static_cast<Size>(num_of_bytes / sizeof(T));
        }

    private:
        bool IsWriteIndexValid(Index index) const noexcept {
            return this -> size_ >= index;
        }

        bool IsReadIndexValid(Index index) const noexcept {
            return this -> size_ > index;
        }

        bool IsWithinRange(Index index, Size count) const noexcept {
            return count <= this -> size_ && (index + count) <= this -> size_;
        }

    private:
        void SetWriteIndex(const std::optional<Index>& index) {
            Index current_index = index ? ToByteSize(*index) : this -> write_index_;

            if (!IsWriteIndexValid(current_index)) {
                throw std::invalid_argument{"An invalid index was passed when calling File<T>::WriteData(...)"};
            }

            file_.seekp(current_index);
        }

        void SetReadIndex(const std::optional<Index>& index) {
            auto current_index = index ? ToByteSize(*index) : this -> read_index_;

            if (!IsReadIndexValid(current_index)) {
                if (index) {
                    throw std::invalid_argument{"An invalid index was passed when calling File<T>::ReadData(...)"};
                }
                
                //if the index was not passed by the user, so the index is set at the beginning of the file
                current_index = 0;
            }

            file_.seekg(current_index);

        }
        
        //returns index of the last inserted byte
        void UpdateWriteIndexAndSize() {
            if (Index current_byte_index = file_.tellp();
                current_byte_index > this -> write_index_) {
                write_index_ = current_byte_index;
                size_ = write_index_; 
            }
        }

        void UpdateReadIndex() {
            read_index_ = file_.tellg();
        }
    
    private: //Data members        
        const Mode MODE_;  
        const fs::path DEFAULT_EXTENSION;

        fs::path filename_;
        
        Size size_;
        Index write_index_;
        Index read_index_;

        std::fstream file_;
    };

    template <typename T>
    class BinaryFile final : public File<T> {
    public:
        BinaryFile() 
        : File<T>(File<T>::Mode::BINARY, "bin"_p) {

        }

        BinaryFile(fs::path filename)
        : File<T>(File<T>::Mode::BINARY, "bin"_p, std::move(filename)) {

        }

        template <typename CompatibleType>
        Index PutInStream(CompatibleType* source
                        , std::optional<Index> index = std::nullopt) = delete;

        template <typename CompatibleType>
        Index GetFromStream(CompatibleType* target
                          , std::optional<Index> index = std::nullopt) = delete;

    };

    class TextFile : public File<char> {
    public:
        TextFile();
        TextFile(fs::path filename);

        std::string Substr(Size count = 1, std::optional<Index> index = std::nullopt);
    };
} //namespace file_handler
#endif // FILE_HANDLER_H
