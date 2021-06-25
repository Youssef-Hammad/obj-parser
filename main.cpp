#include "objparser.h"
#include <fstream>

using namespace std;

int main()
{
    string path = "testing.obj";
    vector<p_face> vertices;
    getVertices(path,vertices);

    cout << "Vertices Size: " << vertices.size() << endl;

    // for(uint16_t i = 0; i < vertices.size(); i++)
    // {
    //     cout << "F"<<i+1<<":\nVertexPos: " << vertices[i].vertex->vecPos.x << " " << vertices[i].vertex->vecPos.y << " " << vertices[i].vertex->vecPos.z << endl;
    //     cout << "VertexTexture: " << vertices[i].vertex->vecTex.x << " " << vertices[i].vertex->vecTex.y << " " << vertices[i].vertex->vecTex.z << endl;
    //     cout << "VertexNormals: " << vertices[i].vertex->vecNormal.x << " " << vertices[i].vertex->vecNormal.y << " " << vertices[i].vertex->vecNormal.z << endl;
    //     cout << endl;
    // }
    
    return 0;
}