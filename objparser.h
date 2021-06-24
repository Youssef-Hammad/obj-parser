#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "parsertypes.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

struct vertix
{
    p_vec3 vecPos;
    p_vec3 vecTex;
    p_vec3 vecNormal;
};

struct face
{
    vertix vertix[3];
};

inline p_vec3 parseLine(std::string line)
{
    std::string currentFloat = "";
    float x=0,y=0,z=0;
    for(int i = 1; i<line.size(); i++) 
    {
        if(line[i]==' '||i==line.size()-1) 
        {
            if(i==line.size()-1)
                currentFloat+=line[i];
            if(currentFloat.size()) 
            {
                if(!x)
                    x = std::stof(currentFloat);
                else if(!y)
                    y = std::stof(currentFloat);
                else
                    z = std::stof(currentFloat);
                currentFloat="";
                continue;
            }
        }
        currentFloat+=line[i];
    }
    return {x,y,z};
}

void getVertices(std::string objPath, face* vertices)
{
    std::vector<p_vec3> vecPositions;
    std::vector<p_vec3> vecTextures;
    std::vector<p_vec3> vecNormals;
    std::ifstream objFile;
    objFile.open(objPath.c_str());
    std::string line;
    while(std::getline(objFile,line)) 
    {

//___________________PARSING V POSITIONS_____________________
        if(line[0]=='v'&&line[1]==' ')
            vecPositions.push_back(parseLine(line));
//___________________PARSING Vt POSITIONS____________________
        if(line[0]=='v'&&line[1]=='t')
            vecTextures.push_back(parseLine(line));
//___________________PARSING Vn POSITIONS____________________
        if(line[0]=='v'&&line[1]=='n')
            vecNormals.push_back(parseLine(line));
    }
}

#endif