#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "parsertypes.h"
#define _GLIBCXX_USE_CXX11_ABI 0
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

std::vector<std::string> split(std::string, char16_t splitter);

p_vec3 parseLine(std::string line);

std::vector<std::string> parseFace(std::string line);

void getVertices(std::string objPath, std::vector<p_face> &vertices);

#endif