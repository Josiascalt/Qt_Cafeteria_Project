#include "file_handler.h"

namespace file_handler {
    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, size_t size) {
            return std::filesystem::path(pathname, pathname + size);
        }
    } //namespace literals

    

    //class TextFile member functions definition
    TextFile::TextFile(const fs::path& path) {
        this -> file_.open(path, std::ios::out | std::ios::in);
        this -> InitProps();
    }

    std::string TextFile::Read(Size count, std::optional<Index> index) 
    {
        std::string target(count, '\0');

        this -> ReadData(target.data(), count, index);

        return target;
    }
        

} //namespace file_handler
