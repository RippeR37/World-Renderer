#ifndef UTILS_FILE_H_INCLUDED
#define UTILS_FILE_H_INCLUDED

#include "Exception.h"

#include <string>
#include <fstream>

namespace Util {

    class File {
        public:
            enum ReadMode {
                Text   = 0,
                Binary = std::fstream::binary, 
            };

        public:
            static std::string read(std::string path, ReadMode mode = ReadMode::Text, bool throwException = false)
                throw(Exception::FatalError);

        private:

    };

}

#endif