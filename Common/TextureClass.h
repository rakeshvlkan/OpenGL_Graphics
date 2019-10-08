#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<vector>
#include<iostream>
#include<string>

class TextureClass
{
public:
	TextureClass();
	TextureClass(char const * path);
	~TextureClass();
	unsigned int GetTextureID();
	std::string GetTextureType();
	std::string GetTexturePath();
	void SetTextureID(unsigned int ID);
	void SetTextureType(std::string type);
	void SetTexturePath(std::string path);
	void Bind(unsigned int TextureUnit);
	void LoadTexture(char const *path);

private:
	unsigned int m_textureID;
	std::string m_type;
	std::string m_path;
};

#endif

