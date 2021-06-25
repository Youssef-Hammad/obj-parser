#include "objparser.h"

std::vector<std::string> split(std::string line, char16_t splitter)
{
    // if(line[0]=='f')
    //     std::cout << line << std::endl;
    std::vector<std::string> ret;
    std::string current = "";
    for(uint32_t i = 0; i<line.size(); i++)
    {
        if(line[i]>='a'&&line[i]<='z')
            continue;
        if(line[i]==splitter||i==line.size()-1)
        {
            if(line.size()-1==i)
                current+=line[i];
            if(current.size())
                ret.push_back(current);
            current="";
            continue;
        }
        current+=line[i];
    }
    // std::cout << "lol" << std::endl;
    // for(uint32_t i = 0; i < ret.size(); i++)
    //     std::cout << ret[i] << std::endl;
    return ret;
}
//parse v,vt,vn lines
p_vec3 parseLine(std::string line)
{
    std::string currentFloat = "";
    float ret[]={0,0,0};
    //std::cout << line << std::endl;
    std::vector<std::string> values = split(line,' ');
    for(uint32_t i = 0; i < values.size(); i++) {
        //std::cout << values[i] << std::endl;
        ret[i]=std::stof(values[i]);
    }
    return {ret[0],ret[1],ret[2]};
}

std::vector<std::string> parseFace(std::string line)
{
    std::vector<std::string> values = split(line,' ');
    std::vector<std::string> ret;
    if(values.size()==4)
    {
        ret.push_back(values[0]+" "+values[1]+" "+values[2]);
        ret.push_back(values[0]+" "+values[2]+" "+values[3]);
    } 
    else
    {
        ret=values;
    }
    return ret;
}

void getVertices(std::string objPath, std::vector<p_face> &vertices)
{
    std::vector<p_vec3> vecPositions;
    std::vector<p_vec3> vecTextures;
    std::vector<p_vec3> vecNormals;
    std::vector<std::string> unparsedFaces;
    std::ifstream objFile;
    objFile.open(objPath.c_str());
    std::string line;
    while(std::getline(objFile,line)) 
    {
        //std::cout << "iteration" << std::endl;
//___________________PARSING V POSITIONS_____________________
        if(line[0]=='v'&&line[1]==' ')
            vecPositions.push_back(parseLine(line));
// ___________________PARSING Vt POSITIONS____________________
        if(line[0]=='v'&&line[1]=='t')
            vecTextures.push_back(parseLine(line));
//___________________PARSING Vn POSITIONS____________________
        if(line[0]=='v'&&line[1]=='n')
            vecNormals.push_back(parseLine(line));
//___________________PARSING Vn POSITIONS____________________
        if(line[0]=='f') 
            unparsedFaces.push_back(line);
    }
    for(uint32_t i = 0; i < unparsedFaces.size(); i++)
    {
        std::vector<std::string> faceValues = split(unparsedFaces[i],' ');
        //std::cout << faceValues.size() << std::endl;
        std::vector<p_vertex> tempVertices;
        for(int j = 0; j < faceValues.size(); j++)
        {
            std::vector<std::string> vertexData = split(faceValues[i],'/');

            tempVertices.push_back({vecPositions[std::stoi(vertexData[0])],vecTextures[std::stoi(vertexData[1])],vecNormals[std::stoi(vertexData[2])]});
        }
        // handling if the face contains 4 vertic
        if(tempVertices.size()==4) {
            p_face tempFace;
            tempFace.vertex[0]=tempVertices[0];
            tempFace.vertex[1]=tempVertices[1];
            tempFace.vertex[2]=tempVertices[2];
            
            vertices.push_back(tempFace);
            
            tempFace.vertex[0]=tempVertices[0];
            tempFace.vertex[1]=tempVertices[3];
            tempFace.vertex[2]=tempVertices[2];

            vertices.push_back(tempFace);
        }
        else if(tempVertices.size()==3)
        {
            p_face tempFace;
            tempFace.vertex[0]=tempVertices[0];
            tempFace.vertex[1]=tempVertices[1];
            tempFace.vertex[2]=tempVertices[2];
            
            vertices.push_back(tempFace);
        }
    }
    //std::cout << vecPositions.size() << " " << vecTextures.size() << " " << vecNormals.size() << " " << unparsedFaces.size() << std::endl;
    // std::cout << "v: " << std::endl;
    // for(int i = 0; i < vecPositions.size(); i++)
    //     std::cout << vecPositions[i].x << " " << vecPositions[i].y << " " << vecPositions[i].z << std::endl;
    // std::cout << std::endl;

    // std::cout << "vt: " << std::endl;
    // for(int i = 0; i < vecTextures.size(); i++)
    //     std::cout << vecTextures[i].x << " " << vecTextures[i].y << " " << vecTextures[i].z << std::endl;
    // std::cout << std::endl;
    // std::cout << "vn: " << std::endl;
    // for(int i = 0; i < vecNormals.size(); i++)
    //     std::cout << vecNormals[i].x << " " << vecNormals[i].y << " " << vecNormals[i].z << std::endl;
    // std::cout << std::endl;
}