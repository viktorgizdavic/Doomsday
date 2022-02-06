//
// Created by matf-rg on 8.11.20..
//

#ifndef PROJECT_BASE_COMMON_H
#define PROJECT_BASE_COMMON_H
#include <fstream>
#include <sstream>
#include <string>

std::string readFileContents(std::string path) {
	    std::ifstream in(path);
	    std::stringstream buffer;
	    buffer << in.rdbuf();
	    return buffer.str();
}

#endif // PROJECT_BASE_COMMON_H
