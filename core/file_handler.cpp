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
    
    fs::path CreatePathObject(fs::path path, bool create_recursively) {
        if (fs::exists(path)) {
            return path;
        }
    
        if (create_recursively) {
            if (path.has_relative_path() && path.has_parent_path()) {
                CreatePathObject(path.parent_path(), true);
            }
        }
    
        if (!path.has_extension()) {
            fs::create_directory(path);
            return path;
        }
        
        static std::ofstream new_file;
        new_file.open(path);
    
        if (new_file) {
            new_file.close();
        } else {
            throw fs::filesystem_error{"Fatal error while creating/opening path object.", path , std::make_error_code(std::errc::io_error)};
        }
        
        return path;
    }

    fs::path CreatePathObject(std::string path_obj, bool create_recursively) {
        auto path = detail::StandardizePath(std::move(path_obj));
        return CreatePathObject(std::move(path));
    }

    fs::path CreatePathObject(const char* path_obj, bool create_recursively) {
        return CreatePathObject(std::string(path_obj));
    }

    


    //class TextFile member functions definition
    TextFile::TextFile(fs::path path) 
    : File<char>(std::move(path), ".txt")
    {
    }

    std::string TextFile::Substr(Size count, std::optional<Index> index) {
        std::string target(count, '\0');
        this -> Read(target.data(), count, index);
        return target;
    }
    
    //class JsonFile member functions definition
    JsonFile::JsonFile(fs::path path, const Type* temp_doc) 
    : File<json::Document>(std::move(path), ".json")
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
