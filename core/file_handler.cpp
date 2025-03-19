#include <string>
#include <exception>

#include "file_handler.h"

namespace file_handler {
    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, size_t size) {
            return std::filesystem::path(pathname, pathname + size);
        }
    } //namespace literals

    //class TextFile member functions definition
    TextFile::TextFile(const fs::path& path) 
    : File<char>(path)
    {
    }

    std::string TextFile::Substr(Size count, std::optional<Index> index) {
        std::string target(count, '\0');
        this -> Read(target.data(), count, index);
        return target;
    }
    
    //class JsonFile member functions definition
    JsonFile::JsonFile(const fs::path& path, const Type* temp_doc) 
    : File<json::Document>(path)
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
