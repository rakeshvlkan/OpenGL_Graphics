#ifndef MESHCLASS_H
#define MESHCLASS_H

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "TextureClass.h"

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

class MeshClass
{
public:
	MeshClass(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureClass> textures);
	~MeshClass();
	void Draw(ShaderManager shader);
	unsigned int getVAO();
	unsigned int getVBO();
	unsigned int getEBO();
	std::vector<Vertex> getVertices();
	std::vector<TextureClass> getTextures();
	std::vector<unsigned int> getIndices();

public:	
	unsigned int VBO, EBO;

	/*  Mesh Data  */
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TextureClass> textures;
	unsigned int VAO;

private:
	void setupMesh();
};

#endif

