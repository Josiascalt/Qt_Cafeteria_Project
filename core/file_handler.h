#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#pragma once

#include <fstream>
#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

namespace file_handler {
using Size = size_t;

    namespace literals {
    std::filesystem::path operator""_p(const char* pathname, Size size);
    } //namespace literals

    namespace exceptions {
    struct ValidationPathError {};
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
            write_pos_ = file_.tellp();
            size_ = write_pos_ / sizeof(Type);

            file_.seekg(0, std::ios::beg);
            read_pos_ = file_.tellg();
        }

        inline void Write(Type* source
                        , Size count = 1
                        , std::optional<size_t> index = std::nullopt) {
            
            auto size_in_bytes = this -> ToByteSize(count);
            auto index_in_bytes = index ? (*index * sizeof(Type)) : this -> write_pos_;
            
            file_.seekp(index_in_bytes);

            if (file_) {
                file_.write(reinterpret_cast<char*>(source), size_in_bytes);

                if (auto current_index = index_in_bytes + size_in_bytes; 
                    current_index > write_pos_) {
                    size_ = current_index / sizeof(Type);
                    write_pos_ = current_index;
                }
            }
        }

        inline void Read(Type* target
                       , Size size = sizeof(Type)
                       , std::optional<Size> pos = std::nullopt) {
                           
            file_.seekg(pos ? *pos : this -> read_pos_);

            if (file_) {
                file_.read(reinterpret_cast<char*>(target), size);
            }

            read_pos_ += size;
        }

        inline Size GetSize() const {
            return size_;
        }

        ~BinaryFile() {
            file_.close();
        }

    private:

        Size ToByteSize(Size num_of_items) {
            return static_cast<Size>(num_of_items * sizeof(Type));
        }
        Size ToElementSize(Size num_of_bytes) {
            return static_cast<Size>(num_of_bytes / sizeof(Type));
        }

    private:
        std::fstream file_;

        Size size_;
        Size write_pos_;
        Size read_pos_;
    };
} //namespace file_handler

#endif // FILE_HANDLER_H
