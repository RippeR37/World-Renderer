#include "File.h"

namespace Util {

    std::string File::read(std::string path, ReadMode mode, bool throwException) {
        std::ifstream fileStream;
        std::string result = "";
        std::string line   = "";

        fileStream.open(path, std::fstream::in | mode);
        if(fileStream.is_open()) {
            while(std::getline(fileStream, line))
                result += "\n" + line;
            fileStream.close();
        } else if(throwException) {
            std::string errorMsg = "Could not open file: '" + path + "'";
            throw Exception::FatalError(errorMsg.c_str());
        }

        return result;
    }

}