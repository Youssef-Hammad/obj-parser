# OBJ-Parser

C++ library that parses `.obj` files into a more usable format

## Current Progress
- Parsing lines starting with v, vt, vn, and f
- Parsing up to 4 vertex faces (converting 4 vertex faces into two 3 vertex faces)

## How to use
First make sure you include the library, after that:
- Create a STL `vector` of type `p_face`
- Add the path to the `.obj` you wish to parse as a `string`
Note: make sure to replace each `\` with `\\` in the path to avoid any bugs
```cpp
vector<p_face> vec;
string path = "C:\\path\\model.obj"
```
After you're done, call `getVertices` and pass the variables we just created
```cpp
getVertices(path,vec);
```
Now the vector `vec` contains the parsed data from your `.obj` file

## Using parsed data
To access a specific vertex inside a specific face from our previously defined STL vector `vec`, simply do the following:
```cpp
vec[i].vertex[j];
```
`i` here refers to the face and `j` refers to a vertex inside the face.
Now to access the vertex data (Position, Texture, or Normal). Simply write one of the following depending on the vertex data you need:
```cpp
vec[i].vertex[j].vecPos;
vec[i].vertex[j].vecTex;
vec[i].vertex[j].vecNormal;
```
All of `vecPos`, `vecTex`, and `vecNormal` are of the same type and accessing their co-ordinates is fairly simple, we'll demonstrate on `vecPos`.
```cpp
vec[i].vertex[j].vecPos.x;
vec[i].vertex[j].vecPos.y;
vec[i].vertex[j].vecPos.z;
```
Now you're all set to use the library.

## Some Extra Information
Convention:
- For datatypes created within the library, I used a prefix `p_` before the datatype name (i.e `p_face`, `p_vertex`, `p_vec3`)

Purpose for creating this library:
- Using it with OpenGL for rendering