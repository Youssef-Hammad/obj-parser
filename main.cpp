#include "objparser.h"
#include <fstream>

using namespace std;

int main()
{
    string path = "testing.obj";
    face* vertices;
    getVertices(path,vertices);
    
    return 0;
}