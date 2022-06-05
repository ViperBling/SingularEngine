#pragma once

#include <string>
#include <fstream>
#include <streambuf>

namespace SingularEngine
{
    class FileLoader
    {
    public:
        static std::string ReadText(const std::string& filePath) {

            std::ifstream  in(filePath);
            std::string contents(
                (std::istreambuf_iterator<char>(in)),
                std::istreambuf_iterator<char>());

            return contents;
        }
    };
}