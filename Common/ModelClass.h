#ifndef MODELCLASS_H
#define MODELCLASS_H

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ShaderManager.h"
#include"TextureClass.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include"MeshClass.h"
#include"TextureClass.h"
#include<GL\glew.h>
#include<GLFW\glfw3.h>

class ModelClass
{
public:
	ModelClass(bool gamma = false);
	~ModelClass();
	void LoadModel(std::string const &path);
	void Draw(ShaderManager shader);
	std::vector<TextureClass> getLoadedTexture();
	std::vector<MeshClass> getMeshes();

private:
	
	void processNode(aiNode *node, const aiScene *scene);
	MeshClass processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<TextureClass> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	std::vector<TextureClass> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<MeshClass> meshes;
	std::string directory;
	bool gammaCorrection;
};

#endif

