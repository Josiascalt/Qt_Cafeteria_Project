#include "file_handler.h"

namespace file_handler {
    namespace literals {
        std::filesystem::path operator""_p(const char* pathname, Size size) {
            return std::filesystem::path(pathname, pathname + size);
        }
    } //namespace literals

    //class BinaryFile member functions definition

} //namespace file_handler
