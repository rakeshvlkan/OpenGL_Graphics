#ifndef  UTILITY_H
#define UTILITY_H

#include<stdlib.h>
#include<time.h>
#include<iostream>
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define SRANDOM srand((unsigned)time(NULL))
struct PersProjInfo
{
	float FOV;
	float Width;
	float Height;
	float zNear;
	float zFar;
};

struct OrthoProjInfo
{
	float r;        // right
	float l;        // left
	float b;        // bottom
	float t;        // top
	float n;        // z near
	float f;        // z far
};

float RandomFloat();
enum InstancingModes { No_Instancing, Shader_Instancing, Hardware_Instancing };
template <typename T> 
std::string tostr(const T& t);



#endif // ! UTILITY_H