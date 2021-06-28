#include "objparser.h"
#include <fstream>

using namespace std;

int main()
{
    string path = "E:\\3D-Models\\Human-Male-Head\\OBJ\\Low Poly.obj";
    //string path = "E:\\3D-Models\\Books\\obj\\obj.obj";
    //string path = "testing.obj";
    vector<p_face> vertices;
    getVertices(path,vertices);

    cout << "Faces Size: " << vertices.size() << endl;

    // for(uint16_t i = 0; i < vertices.size(); i++)
    // {
    //     cout << "F " << i+1 << ":" << endl;
    //     for(int j = 0; j < 3; j++) {
    //         cout << "Position: " << vertices[i].vertex[j].vecPos.x << " " << vertices[i].vertex[j].vecPos.y << " " << vertices[i].vertex[j].vecPos.z << endl;
    //         cout << "Texture: " << vertices[i].vertex[j].vecTex.x << " " << vertices[i].vertex[j].vecTex.y << " " << vertices[i].vertex[j].vecTex.z << endl;
    //         cout << "Normal: " << vertices[i].vertex[j].vecNormal.x << " " << vertices[i].vertex[j].vecNormal.y << " " << vertices[i].vertex[j].vecNormal.z << endl;
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    
    return 0;
}