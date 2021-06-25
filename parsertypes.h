#ifndef PARSERTYPES_H
#define PARSERTYPES_H

struct p_vec3
{
    float x;
    float y;
    float z;
    p_vec3(float xx=0.0f,float yy=0.0f,float zz=0.0f)
    {
        x=xx;
        y=yy;
        z=zz;
    }
};

struct p_vertex
{
    p_vec3 vecPos;
    p_vec3 vecTex;
    p_vec3 vecNormal;
};

struct p_face
{
    p_vertex vertex[3];
};

#endif
