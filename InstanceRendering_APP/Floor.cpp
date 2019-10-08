#include "Floor.h"
#include "FileClass.h"

float m_floorVertices[] = {
	// positions          // texture Coords 
	400.0f, -0.400f,  400.0f,  0.0f, 1.0f, 0.0f, 2.0f, 0.0f,
	-400.0f, -0.400f,  400.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-400.0f, -0.400f, -400.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f,

	400.0f, -0.400f,  400.0f, 0.0f, 1.0f, 0.0f,  2.0f, 0.0f,
	-400.0f, -0.400f, -400.0f, 0.0f, 1.0f, 0.0f,  0.0f, 2.0f,
	400.0f, -0.400f, -400.0f, 0.0f, 1.0f, 0.0f,  2.0f, 2.0f
};

Floor::Floor(CameraClass *camera)
{   

	m_pFloorShader = new ShaderManager(); 
	 m_pCamera = camera;
	 m_pTexture = new TextureClass();
	 m_pFloorModel = new ModelClass();
}

Floor::~Floor()
{
}

void Floor::Init()
{ 
	m_pTexture->LoadTexture(FileClass::getPath("resources/textures/marble.jpg").c_str());
	m_pFloorShader->AddShaders("floor.vs", "floor.fs");
	lightPos = glm::vec3(250.0f, 20.0, -85.0);
	m_blinn = false;
	glGenVertexArrays(1, &m_floorVAO);
	glGenBuffers(1, &m_floorVBO);
	glBindVertexArray(m_floorVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_floorVertices), &m_floorVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

void Floor::Render()
{   
	glBindVertexArray(m_floorVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureID());
	m_pFloorShader->use();
	glm::mat4 floorModel = glm::mat4(1.0);
	glm::mat4 projection = m_pCamera->getPerspectiveProjection();
	glm::mat4 view = m_pCamera->GetViewMatrix();
	glm::translate(floorModel, glm::vec3(200.0f, 0.0f, 0.0f));	
	m_pFloorShader->setMat4("model", floorModel);
	m_pFloorShader->setMat4("projection", projection);
	m_pFloorShader->setMat4("view", view);
	m_pFloorShader->setVec3("viewPos", m_pCamera->Position);
	m_pFloorShader->setVec3("lightPos", lightPos);
	m_pFloorShader->setInt("blinn", m_blinn);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Floor::setBlinn(bool blinn)
{  
	m_blinn = blinn;
}

bool Floor::getBlinn()
{
	return m_blinn;;
}
