#ifndef CUBEMAPTEXTURE_H
#define CUBEMAPTEXTURE_H
#include<iostream>
#include<vector>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <stb_image.h>
#include<string>

using namespace std;

class CubemapTexture
{
public:

	CubemapTexture(vector<string> faces);

	~CubemapTexture();
	unsigned int getTextureID();
	void Bind(unsigned int TextureUnit);

private:	
	unsigned int m_textureObj;
};

#endif

