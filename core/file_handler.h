    #ifndef FILE_HANDLER_H
    #define FILE_HANDLER_H
    #pragma once

    #include <fstream>
    #include <filesystem>
    #include <exception>
    #include <optional>

    namespace fs = std::filesystem;

    namespace file_handler {

        using Size = size_t;
        using Index = size_t;

        namespace literals {
        std::filesystem::path operator""_p(const char* pathname, Size size);
        } //namespace literals

        namespace exceptions {
        struct ValidationPathError {};
        struct InvalidIndex {};
        } //namespace exceptions

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
                        throw exceptions::ValidationPathError{};
                    }

                }
                else {
                    fs::create_directory(path);
                }
            }

            return path;
        }

        template <typename T>
        class BinaryFile {
        public:
            typedef T Type; 
        public:
            BinaryFile(const fs::path& path)
            : file_(path, std::ios::out | std::ios::in | std::ios::binary) 
            {
                file_.seekp(0, std::ios::end);
                write_index_ = file_.tellp();
                size_ = write_index_ / sizeof(Type);

                file_.seekg(0, std::ios::beg);
                read_index_ = file_.tellg();
            }

            void Write(Type* source
                    , Size count = 1
                    , std::optional<Index> index = std::nullopt) {
                
                auto bytes_to_write = this -> ToByteSize(count);
                auto byte_index = index && this -> IsWriteIndexValid(*index) 
                                ? this -> ToByteSize(*index) 
                                : this -> write_index_;

                file_.seekp(byte_index);

                if (file_) {
                    file_.write(reinterpret_cast<char*>(source), bytes_to_write);

                    if (auto current_byte_index = byte_index + bytes_to_write; 
                        current_byte_index > write_index_) {
                        size_ = this -> ToElementSize(current_byte_index);
                        write_index_ = current_byte_index;
                    }
                }
            }

            void Read(Type* target
                    , Size count = 1
                    , std::optional<Index> index = std::nullopt) {

                auto bytes_to_read = this -> ToByteSize(count);
                auto byte_index = index && this -> IsReadIndexValid(*index) && this -> IsWithinRange(*index, count)
                                ? this -> ToByteSize(*index) 
                                : this -> read_index_;

                file_.seekg(byte_index);

                if (file_) {
                    file_.read(reinterpret_cast<char*>(target), bytes_to_read);
                    
                    read_index_ = byte_index + bytes_to_read;
                }
            }

            Size GetSize() const {
                return size_;
            }

            ~BinaryFile() {
                file_.close();
            }

        private:
            bool IsWriteIndexValid(Index index) const {
                if (index > this -> size_) {
                    throw exceptions::InvalidIndex{};

                    return false;
                }
                
                return true;
            }

            bool IsReadIndexValid(Index index) const {
                if (index >= this -> size_) {
                    throw exceptions::InvalidIndex{};

                    return false;
                }
                
                return true;
            }

            bool IsWithinRange(Index index, Size count) const {
                if ((index + count) > this -> size_) {
                    throw std::out_of_range{"The sum of the arguments <index> and <count> is greater than the current elements count."};

                    return false;
                }

                return true;
            }

            Size ToByteSize(Size num_of_items) const {
                return static_cast<Size>(num_of_items * sizeof(Type));
            }

            Size ToElementSize(Size num_of_bytes) const {
                return static_cast<Size>(num_of_bytes / sizeof(Type));
            }

        private:
            std::fstream file_;

            Size size_;
            Index write_index_;
            Index read_index_;
        };
    } //namespace file_handler

    #endif // FILE_HANDLER_H
