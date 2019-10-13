#include "InstancedRendering.h"
#include "Utility.h"
#include<math.h>


InstancedRendering::InstancedRendering(CameraClass *camera)
{
	m_instanceShader = new ShaderManager();
	m_noInstanceShader = new ShaderManager();
	m_camera = camera;
	m_text = NULL;
	m_instanceModel = NULL;
	m_instancingOptions = InstancingModes::No_Instancing;
	m_numModels = NUM_INSTANCES;
}

InstancedRendering::~InstancedRendering()
{
}

void InstancedRendering::Init(std::string const & path)
{ 
	m_instanceShader->AddShaders("instanceRender.vs", "instanceRender.fs");
	m_noInstanceShader->AddShaders("noInstance.vs", "noInstance.fs");
	m_instanceModel = new ModelClass();
	m_instanceModel->LoadModel(path);
	m_modelMatrices = new glm::mat4[NUM_INSTANCES];
	CalInstacedPositions();
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, NUM_INSTANCES * sizeof(glm::mat4), &m_modelMatrices[0], GL_STATIC_DRAW);

	// set transformation matrices as an instance vertex attribute (with divisor 1)
	// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
	// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
	// -----------------------------------------------------------------------------------------------------------------------------------
	for (unsigned int i = 0; i < m_instanceModel->getMeshes().size(); i++)
	{
		unsigned int VAO = m_instanceModel->getMeshes()[i].getVAO();
		glBindVertexArray(VAO);
		// set attribute pointers for matrix (4 times vec4)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}

void InstancedRendering::Render()
{   	
	// configure transformation matrices
	glm::mat4 projection = m_camera->getPerspectiveProjection();
	glm::mat4 view = m_camera->GetViewMatrix();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	if (m_instancingOptions == InstancingModes::No_Instancing)
	{
		m_noInstanceShader->use();
		m_noInstanceShader->setMat4("projection", projection);
		m_noInstanceShader->setMat4("view", view);
		m_noInstanceShader->setInt("texture_diffuse1", 0);

		for (int i = 0; i < NUM_INSTANCES; i++)
		{
			m_noInstanceShader->setMat4("model", m_modelMatrices[i]);
			m_instanceModel->Draw(*m_noInstanceShader);
		}
	}
	else if (m_instancingOptions == InstancingModes::Hardware_Instancing)
	{
		// draw meteorites
		m_instanceShader->use();
		m_instanceShader->setMat4("projection", projection);
		m_instanceShader->setMat4("view", view);
		m_instanceShader->setInt("texture_diffuse1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_instanceModel->getLoadedTexture()[0].GetTextureID()); // note: we also made the textures_loaded vector public (instead of private) from the model class.
		for (unsigned int i = 0; i < m_instanceModel->getMeshes().size(); i++)
		{
			glBindVertexArray(m_instanceModel->getMeshes()[i].getVAO());
			glDrawElementsInstanced(GL_TRIANGLES, m_instanceModel->getMeshes()[i].indices.size(), GL_UNSIGNED_INT, 0, NUM_INSTANCES);
			glBindVertexArray(0);
		}
	}
}

void InstancedRendering::setBlinn(bool blinn)
{ 
	m_floor->setBlinn(blinn);
}

bool InstancedRendering::getBlinn()
{
	return m_floor->getBlinn();
}

void InstancedRendering::setInstancingOptions(InstancingModes modes)
{ 
	m_instancingOptions = modes;
}

int InstancedRendering::getNumberOfModels()
{
	return m_numModels;
}

void InstancedRendering::CalInstacedPositions()
{
	for (unsigned int i = 0; i < NUM_ROWS; i++) {
		for (unsigned int j = 0; j < NUM_COLS; j++) {
			unsigned int Index = i * NUM_COLS + j;
			m_InstancePositions[Index].x = RandomFloat() * 350.0f;
			m_InstancePositions[Index].y = 0.0f;
			m_InstancePositions[Index].z = -(RandomFloat() * 350.0f);
		}
	}

	for (unsigned int i = 0; i < NUM_INSTANCES; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 Pos(m_InstancePositions[i]);
		model = glm::translate(model, Pos);
		m_modelMatrices[i] = model;
	}
}




	