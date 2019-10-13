#ifndef INSTANCED_RENDERING_H
#define INSTANCED_RENDERING_H
#include"CameraClass.h"
#include"ShaderManager.h"
#include "TextureClass.h"
#include "ModelClass.h"
#include "SkyBox.h"
#include "Floor.h"
#include "Text.h"
#include "FileClass.h"
#include "CallBacks.h"
#include "DevApp.h"
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include"Utility.h"

#define NUM_COLS 200
#define NUM_ROWS 200
#define NUM_INSTANCES NUM_COLS * NUM_ROWS
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

class InstancedRendering : public ICallbacks, public DevApp
{
public:
	InstancedRendering(CameraClass *camera);
	~InstancedRendering();
	void Init(std::string const &path);
	void Render();
	void setBlinn(bool blinn);
	bool getBlinn();	
	void setInstancingOptions(InstancingModes modes);
	int getNumberOfModels();

private:
	void CalInstacedPositions();

private:

	bool m_hardwareInstancing;
	bool m_shaderInstancing;
	unsigned int m_screenWidth;
	unsigned int m_screenHeight;
	bool m_blinn;
	bool m_blinnKeyPressed;
	CameraClass *m_camera;
	glm::vec3 m_InstancePositions[NUM_INSTANCES];
	float m_lastX;
	float m_lastY;
	float m_firstMouse;
	float m_deltaTime;
	float m_lastFrame;
	float m_scale;
	ModelClass *m_instanceModel;
	ShaderManager *m_instanceShader;
	ShaderManager *m_noInstanceShader;
	SkyBox *m_skyBox;
	Floor *m_floor;
	Text *m_text;	
	InstancingModes m_instancingOptions;
	int m_numModels;	
	glm::mat4* m_modelMatrices;
};

#endif
