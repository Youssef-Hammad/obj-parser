#ifndef OBJPARSER_H
#define OBJPARSER_H

#include "parsertypes.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

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

p_vec3 parseLine(std::string line)
{
    std::string currentFloat = "";
    float x=0,y=0,z=0;
    //std::cout << line << std::endl;
    for(int i = 2; i<line.size(); i++) 
    {
        if(line[i]==' '||i==line.size()-1) 
        {
            if(i==line.size()-1)
                currentFloat+=line[i];
            if(currentFloat.size()) 
            {
                //std::cout << currentFloat << std::endl;
                if(!x)
                    x = std::stof(currentFloat);
                else if(!y)
                    y = std::stof(currentFloat);
                else
                    z = std::stof(currentFloat);
                currentFloat="";
            }
            continue;
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
    std::cout << "v: " << std::endl;
    for(int i = 0; i < vecPositions.size(); i++)
        std::cout << vecPositions[i].x << " " << vecPositions[i].y << " " << vecPositions[i].z << std::endl;
    std::cout << std::endl;

    std::cout << "vt: " << std::endl;
    for(int i = 0; i < vecTextures.size(); i++)
        std::cout << vecTextures[i].x << " " << vecTextures[i].y << " " << vecTextures[i].z << std::endl;
    std::cout << std::endl;
    std::cout << "vn: " << std::endl;
    for(int i = 0; i < vecNormals.size(); i++)
        std::cout << vecNormals[i].x << " " << vecNormals[i].y << " " << vecNormals[i].z << std::endl;
    std::cout << std::endl;

    
}

#endif