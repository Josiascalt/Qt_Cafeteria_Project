#include "document_types.h"

namespace file_handler {
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