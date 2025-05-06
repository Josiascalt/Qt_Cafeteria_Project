#ifndef DOCUMENT_TYPES_H
#define DOCUMENT_TYPES_H
#pragma once

#include "file_handler\file_handler.h"
#include "json\json.h"

namespace file_handler {
    class JsonFile : public File<json::Document> {
    public:
        JsonFile(const Type* temp_doc = nullptr);
        JsonFile(fs::path filename, const Type* temp_doc = nullptr);
        Type Get();
        void Override(const Type* doc);
        void Restore();
    private:
        const Type* temp_doc_;
    };
} //namespace file_handler

#endif // DOCUMENT_TYPES_H