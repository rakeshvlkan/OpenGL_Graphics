#ifndef SKYBOX_h
#define SKYBOX_h

#include"CameraClass.h"
#include"CubeMapTexture.h"
#include "ModelClass.h"
#include"MeshClass.h"
#include<iostream>
#include<vector>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"FileClass.h"

//skyboxVertices.  (glm::vec3(-1.0f, 1.0f, -1.0f))
//	// positions          
//	-1.0f,  1.0f, -1.0f,
//	-1.0f, -1.0f, -1.0f,
//	1.0f, -1.0f, -1.0f,
//	1.0f, -1.0f, -1.0f,
//	1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	1.0f, -1.0f, -1.0f,
//	1.0f, -1.0f,  1.0f,
//	1.0f,  1.0f,  1.0f,
//	1.0f,  1.0f,  1.0f,
//	1.0f,  1.0f, -1.0f,
//	1.0f, -1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	1.0f,  1.0f,  1.0f,
//	1.0f,  1.0f,  1.0f,
//	1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	-1.0f,  1.0f, -1.0f,
//	1.0f,  1.0f, -1.0f,
//	1.0f,  1.0f,  1.0f,
//	1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	1.0f, -1.0f, -1.0f,
//	1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	1.0f, -1.0f,  1.0f
//};

class SkyBox
{
public:
	SkyBox(CameraClass *camera);
	~SkyBox();

	void Init(std::vector<std::string> faces);

	void Render();
private:

	CameraClass* m_pCamera;
	CubemapTexture* m_pCubemapTex;
	ModelClass* m_pModel;
	ShaderManager* m_skyBoxShader;
	std::vector<glm::vec3> m_skyboxVertices;
	unsigned int m_skyboxVAO, m_skyboxVBO;
};

#endif

