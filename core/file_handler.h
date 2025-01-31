#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#pragma once

#include <fstream>
#include <filesystem>
//#include <exception>
#include <optional>
#include <cstdint>
#include <array>

namespace fs = std::filesystem;

namespace file_handler {

    using Size = uint_fast64_t;
    using Index = uint_fast64_t;

    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, size_t size);
    } //namespace literals

    using namespace literals;

    inline static fs::path CreatePathObject(const char* path_to_validate, const fs::path& parent_path = ""_p) {
        fs::path path = parent_path / fs::path(path_to_validate);
        if (!std::filesystem::exists(path)) {
            if (path.has_extension()) {
                static std::ofstream new_file;
                new_file.open(path);
                if (new_file) {
                    new_file.close();
                }
                else {
                    throw fs::filesystem_error{"Fatal error while creating/opening path object.", path , std::make_error_code(std::errc::io_error)};
                }

            }
            else {
                fs::create_directory(path);
            }
        }

        return path;
    }
    
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
        File() = default;

        Size GetSize() const {
            return this -> ToElementSize(this -> size_);
        }

    protected:
        virtual void InitProps() {
            file_.seekp(0, std::ios::end);
            write_index_ = file_.tellp();
            size_ = write_index_;

            file_.seekg(0, std::ios::beg);
            read_index_ = file_.tellg(); 
        }

        template <typename CompatibleType, typename Func>
        void WriteData(CompatibleType* source
                     , Func write_func
                     , std::optional<Index> index) {

            if (!source) {
                throw std::invalid_argument{"A nullptr was passed when calling File<T>::WriteData(...)"};
            }
            
            Index current_index = index ? ToByteSize(*index) : this -> write_index_;

            if (!this -> IsWriteIndexValid(current_index)) {
                throw std::invalid_argument{"An invalid index was passed when calling File<T>::WriteData(...)"};
            }

            file_.seekp(current_index);

            if (!file_) {
                throw fs::filesystem_error {"Attempt to write in invalid file.", std::make_error_code(std::errc::io_error)};
            } 

            write_func(source);

            if (Index current_byte_index = file_.tellp(); 
                current_byte_index > this -> write_index_) {
                write_index_ = current_byte_index;
                size_ = write_index_; 
            }
        }

        void ReadData(T* target
                    , Size count
                    , std::optional<Index> index) {
            if (count == 0) {
                return;
            }

            if (!target) {
                throw std::invalid_argument{"A nullptr was passed when calling File<T>::ReadData(...)"};
            }

            auto current_index = index ? ToByteSize(*index) : this -> read_index_;

            if (!this -> IsReadIndexValid(current_index)) {
                if (index) {
                    throw std::invalid_argument{"An invalid index was passed when calling File<T>::ReadData(...)"};
                }
                
                //if the index was not passed by the user, so the index is set at the beginning of the file
                current_index = 0;
            }

            auto bytes_to_read = this -> ToByteSize(count);

            if (IsWithinRange(current_index, bytes_to_read)) {
                throw std::out_of_range{"When calling File<T>::ReadData(...), the required amount of data to read exceeds the existent data"};
            }          

            file_.seekg(current_index);

            if (!file_) {
                throw fs::filesystem_error {"Attempt to read an invalid file.", std::make_error_code(std::errc::io_error)};
            } 
            
            file_.read(reinterpret_cast<char*>(target), bytes_to_read);
            
            read_index_ = current_index + bytes_to_read;
            
        }

        ~File() {
            file_.close();
        }

    //private:
        Size ToByteSize(Size num_of_items) const {
            return static_cast<Size>(num_of_items * sizeof(T));
        }

        Size ToElementSize(Size num_of_bytes) const {
            return static_cast<Size>(num_of_bytes / sizeof(T));
        }

        bool IsWriteIndexValid(Index index) const noexcept {
            return this -> size_ >= index;
        }

        bool IsReadIndexValid(Index index) const noexcept {
            return this -> size_ > index;
        }

        bool IsWithinRange(Index index, Size count) const noexcept {
            return count <= this -> size_ && (index + count) > this -> size_;
        }

    protected:
        std::fstream file_;

        Size size_;
        Index write_index_;
        Index read_index_;
    };

    template <typename T>
    class BinaryFile : public File<T> {
    public:
        typedef T Type;
    public:
        BinaryFile(const fs::path& path)
        {
            this -> file_.open(path, std::ios::out | std::ios::in | std::ios::binary);
            this -> InitProps();
        }

        void Write(Type* source
                 , Size count = 1
                 , std::optional<Index> index = std::nullopt) 
        {
            auto count_in_bytes = this -> ToByteSize(count);
            auto func = [&](Type* data){this -> file_.write(reinterpret_cast<char*>(data), count_in_bytes);};
            this -> WriteData(source, func, index);
        }

        void Read(Type* source
                 , Size count = 1
                 , std::optional<Index> index = std::nullopt) 
        {
            this -> ReadData(source, count, index);
        }
    };

    class TextFile : public File<char> {
    public:
        TextFile(const fs::path& path);

        template <typename T>
        void Write(T* data, std::optional<Index> index = std::nullopt) {
            auto func = [&](T* data){this -> file_ << *data;};
            this -> WriteData(data, func, index);
        }

        std::string Read(Size count = 1, std::optional<Index> index = std::nullopt);
    };
    
} //namespace file_handler
#endif // FILE_HANDLER_H
