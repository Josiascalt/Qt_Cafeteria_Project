#include <string>
#include <exception>

#include "file_handler.h"

namespace file_handler {
    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, size_t size) {
            return std::filesystem::path(pathname, pathname + size);
        }
    } //namespace literals
    namespace detail {
        fs::path StandardizePath(std::string path) {
            for (size_t i = 0; i < path.size(); ++i) {
                char c = path[i];
            #if defined(_WIN32)
                    if (c == '/') {
                        path[i] = '\\';
                    }
            #else
                    if (c == '\\') {
                        path[i] == '/';
                    }
            #endif
            }

            return fs::path{std::move(path)};
        }
    }//namespace detail
    
    void CreateFileSystemObject(const fs::path& path, bool create_recursively) {
        if (fs::exists(path)) {
            return;
        }
    
        if (create_recursively) {
            if (path.has_relative_path() && path.has_parent_path()) {
                CreateFileSystemObject(path.parent_path(), true);
            }
        }
    
        if (!path.has_extension()) {
            fs::create_directory(path);
            return;
        }
        
        static std::ofstream new_file;
        new_file.open(path);
    
        if (new_file) {
            new_file.close();
        } else {
            throw fs::filesystem_error{"Fatal error while creating/opening path object.", path , std::make_error_code(std::errc::io_error)};
        }
    }

    fs::path MakeValidPath(fs::path&& path, bool create_recursively) {
        CreateFileSystemObject(path, create_recursively);
        
        return path;
    }

    fs::path MakeValidPath(std::string path_obj, bool create_recursively) {
        return MakeValidPath(detail::StandardizePath(std::move(path_obj)), create_recursively);
    }

    fs::path MakeValidPath(const char* path_obj, bool create_recursively) {
        return MakeValidPath(std::string(path_obj), create_recursively);
    }

    


    //class TextFile member functions definition
    TextFile::TextFile()
    : File<char>(File<char>::Mode::TEXT, "txt"_p) {

    }
    TextFile::TextFile(fs::path filename) 
    : File<char>(File<char>::Mode::TEXT, "txt"_p, std::move(filename)) {

    }

    std::string TextFile::Substr(Size count, std::optional<Index> index) {
        std::string target(count, '\0');
        this -> Read(target.data(), count, index);
        return target;
    }
    
    //class JsonFile member functions definition
    JsonFile::JsonFile(const Type* temp_doc) 
    : File<json::Document>(File<json::Document>::Mode::TEXT, "json"_p)
    , temp_doc_(temp_doc)
    {
    }
    JsonFile::JsonFile(fs::path filename, const Type* temp_doc) 
    : File<json::Document>(File<json::Document>::Mode::TEXT, "json"_p, std::move(filename))
    , temp_doc_(temp_doc)
    {
    }

    JsonFile::Type JsonFile::Get() {
        try {
            JsonFile::Type doc(json::Node{});
            this->GetFromStream(&doc);
            return doc;
        } catch (json::ParsingError& e) {
            Restore();
        }

        return Type(json::Node{});
    }

    void JsonFile::Override(const JsonFile::Type* doc) {
        if (doc) {
            if (!this->IsEmpty()) {
                this->Reset();
            }

            this->PutInStream(doc);
        }
    }

    void JsonFile::Restore() {
        this->Reset();

        if (temp_doc_) {
            this->Override(temp_doc_);
        } 
    }

} //namespace file_handler
