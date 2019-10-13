#ifndef FLOOR_H
#define FLOOR_H

#include"CameraClass.h"
#include"CubeMapTexture.h"
#include"MeshClass.h"
#include"TextureClass.h"
#include<iostream>
#include<vector>
#include"ModelClass.h"
#include "Utility.h"

class Floor
{
public:
	Floor(CameraClass *camera);
	~Floor();

	void Init();
	void Render();
	void setBlinn(bool blinn);
	bool getBlinn();

private:
	CameraClass* m_pCamera;
	TextureClass* m_pTexture;
	ShaderManager* m_pFloorShader;	
	unsigned int m_floorVAO, m_floorVBO;
	glm::vec3 lightPos;
	bool m_blinn;
};

#endif

