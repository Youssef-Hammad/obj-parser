#include "objparser.h"

std::vector<std::string> split(std::string line, char16_t splitter)
{
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
    return ret;
}
//parse v,vt,vn lines
p_vec3 parseVertexData(std::string line)
{
    std::string currentFloat = "";
    float ret[]={0,0,0};
    std::vector<std::string> values = split(line,' ');
    for(uint32_t i = 0; i < values.size(); i++) {
        ret[i]=std::stof(values[i]);
    }
    return {ret[0],ret[1],ret[2]};
}

std::vector<p_vertex> parseFace(std::string line, const std::vector<p_vec3> &vecPos, const std::vector<p_vec3> &vecTex, const std::vector<p_vec3> &vecNormal)
{
    std::vector<std::string> faceValues = split(line,' ');
    std::vector<p_vertex> ret;
    for(int j = 0; j < faceValues.size(); j++)
    {
        std::vector<std::string> vertexData = split(faceValues[j],'/');
        while(vertexData.size()<3) 
        {
            vertexData.push_back("0");
        }
        ret.push_back({vecPos[std::stoi(vertexData[0])],vecTex[std::stoi(vertexData[1])],vecNormal[std::stoi(vertexData[2])]});
    }
    return ret;
}

void getVertices(std::string objPath, std::vector<p_face> &vertices)
{
    std::vector<p_vec3> vecPositions;
    vecPositions.push_back({0,0,0});
    std::vector<p_vec3> vecTextures;
    vecTextures.push_back({0,0,0});
    std::vector<p_vec3> vecNormals;
    vecNormals.push_back({0,0,0});
    std::vector<std::string> unparsedFaces;
    std::ifstream objFile;
    objFile.open(objPath.c_str());
    std::string line;
    while(std::getline(objFile,line)) 
    {
//___________________PARSING V POSITIONS_____________________
        if(line[0]=='v'&&line[1]==' ')
            vecPositions.push_back(parseVertexData(line));
// ___________________PARSING Vt POSITIONS____________________
        if(line[0]=='v'&&line[1]=='t')
            vecTextures.push_back(parseVertexData(line));
//___________________PARSING Vn POSITIONS____________________
        if(line[0]=='v'&&line[1]=='n')
            vecNormals.push_back(parseVertexData(line));
//___________________PARSING Vn POSITIONS____________________
        if(line[0]=='f') 
            unparsedFaces.push_back(line);
    }
    for(uint32_t i = 0; i < unparsedFaces.size(); i++)
    {
        std::vector<p_vertex> parsedVertex = parseFace(unparsedFaces[i],vecPositions,vecTextures,vecNormals);
        
        p_face parsedFace;

        // handling if the face contains 4 vertices
        if(parsedVertex.size()==4) 
        {
            parsedFace.vertex[0]=parsedVertex[0];
            parsedFace.vertex[1]=parsedVertex[1];
            parsedFace.vertex[2]=parsedVertex[2];
            
            vertices.push_back(parsedFace);
            
            parsedFace.vertex[0]=parsedVertex[0];
            parsedFace.vertex[1]=parsedVertex[3];
            parsedFace.vertex[2]=parsedVertex[2];

            vertices.push_back(parsedFace);
        }
        else if(parsedVertex.size()==3)
        {
            parsedFace.vertex[0]=parsedVertex[0];
            parsedFace.vertex[1]=parsedVertex[1];
            parsedFace.vertex[2]=parsedVertex[2];
            
            vertices.push_back(parsedFace);
        }
    }
    objFile.close();
}