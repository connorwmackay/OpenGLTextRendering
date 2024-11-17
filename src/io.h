#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <sstream>

class File_IO {
    public:
        File_IO() {}

        static const std::string read_file(const std::string& fileName) {
            std::string file_data;

            std::ifstream file_stream (fileName);
            
            std::stringstream data_sstream;
            data_sstream << file_stream.rdbuf();

            file_data = data_sstream.str();

            file_stream.close();
            return file_data;
        }

        static void write_file(const std::string& fileName, const std::string& data) {
            std::ofstream file_stream (fileName);
            file_stream << data;
            file_stream.close();
        }
};

#endif