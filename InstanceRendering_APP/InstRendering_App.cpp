#include<windows.h>
#include<sysinfoapi.h>
#include"InstancedRendering.h"
#include "CallBacks.h"
#include "DevApp.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include "Glfw_Backend.h"
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

vector<std::string> faces
{
	FileClass::getPath("resources/textures/skybox/right.jpg"),
	FileClass::getPath("resources/textures/skybox/left.jpg"),
	FileClass::getPath("resources/textures/skybox/top.jpg"),
	FileClass::getPath("resources/textures/skybox/bottom.jpg"),
	FileClass::getPath("resources/textures/skybox/front.jpg"),
	FileClass::getPath("resources/textures/skybox/back.jpg")
};

class App1 : public ICallbacks, public DevApp
{
public:
	App1()
	{
		m_pGameCamera = NULL;
		m_pGround = NULL;
		m_pInstancedRendering = NULL;
		m_pSkyBox = NULL;
		m_pFloor = NULL;
		m_pText = NULL;
		m_persProjInfo.FOV = 60.0f;
		m_persProjInfo.Height = WINDOW_HEIGHT;
		m_persProjInfo.Width = WINDOW_WIDTH;
		m_persProjInfo.zNear = 1.0f;
		m_persProjInfo.zFar = 100.0f;
		m_currentTimeMillis = GetTickCount();
		blinnKeyPressed = false;
		blinn = false;
		float lastX = (float)WINDOW_WIDTH / 2.0;
		float lastY = (float)WINDOW_HEIGHT / 2.0;
		firstMouse = true;
		m_instancingOptions = InstancingModes::Hardware_Instancing;
	}
	virtual ~App1()
	{
		SAFE_DELETE(m_pGameCamera);
		SAFE_DELETE(m_pGround);
		SAFE_DELETE(m_pInstancedRendering);
	}

	void Init()
	{
		m_pGameCamera = new CameraClass(glm::vec3(250.0f, 15.0, 50.0));
		m_pGameCamera->setPerpectiveProjection(WINDOW_WIDTH, WINDOW_HEIGHT);
		m_pGameCamera->setOrthographicProjection(WINDOW_WIDTH, WINDOW_HEIGHT);

		m_pFloor = new Floor(m_pGameCamera);
		m_pFloor->Init();

		m_pInstancedRendering = new InstancedRendering(m_pGameCamera);
		m_pInstancedRendering->Init(FileClass::getPath("resources/objects/rock/rock.obj").c_str());

		m_pSkyBox = new SkyBox(m_pGameCamera);
		m_pSkyBox->Init(faces);

		m_pText = new Text(m_pGameCamera);
		m_pText->Init();
		m_pText->setNumberOfModels(m_pInstancedRendering->getNumberOfModels());
	}

	void RenderScene()
	{
		CalcFPS();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_pFloor->Render();
		m_pFloor->setBlinn(blinn);
		m_pInstancedRendering->setInstancingOptions(m_instancingOptions);
		m_pInstancedRendering->Render();
		m_pSkyBox->Render();
		m_pText->Render();
		m_pText->setFPS(getFPS());
		m_pText->setInstancingMode(m_instancingOptions);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	virtual void framebuffer_size_callback(int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	virtual	void mouse_callback(double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		m_pGameCamera->ProcessMouseMovement(xoffset, yoffset);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	virtual void scroll_callback(double xoffset, double yoffset)
	{
		m_pGameCamera->ProcessMouseScroll(yoffset);
	}

	virtual void KeyboardCB(int key, bool state)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			if (state)
			{
				m_pGameCamera->ProcessKeyboard(FORWARD, 0.05);
			}
			break;
		case GLFW_KEY_S:
			if (state)
			{
				m_pGameCamera->ProcessKeyboard(BACKWARD, 0.05);
			}
			break;
		case GLFW_KEY_A:
			if (state)
			{
				m_pGameCamera->ProcessKeyboard(LEFT, 0.05);
			}
			break;
		case GLFW_KEY_D:
			if (state)
			{
				m_pGameCamera->ProcessKeyboard(RIGHT, 0.05);
			}
			break;
		case GLFW_KEY_B:
			if (state && !blinnKeyPressed)
			{
				blinn = !blinn;
				blinnKeyPressed = true;
			}
			if (!state)
			{
				blinnKeyPressed = false;
			}
			break;
		case GLFW_KEY_H:
			if (state)
			{
				m_instancingOptions = InstancingModes::Hardware_Instancing;
			}
			break;
		case GLFW_KEY_N:
			if (state)
			{
				m_instancingOptions = InstancingModes::No_Instancing;
			}
			break;
		case GLFW_KEY_M:
			if (state)
			{
				m_instancingOptions = InstancingModes::Shader_Instancing;
			}
			break;
		}
	}

	void Run()
	{
		GLFWBackendRun(this);
	}

private:
	long long m_currentTimeMillis;
	CameraClass* m_pGameCamera;
	ModelClass* m_pGround;
	Floor* m_pFloor;
	InstancedRendering *m_pInstancedRendering;
	PersProjInfo m_persProjInfo;
	SkyBox *m_pSkyBox;
	Text *m_pText;
	bool blinnKeyPressed;
	bool blinn;
	float lastX;
	float lastY;
	bool firstMouse;
	unsigned int m_deltaTimeMillis;
	InstancingModes m_instancingOptions;
};

int main(int argc, char** argv)
{
	GLFWBackendInit(argc, argv);

	if (!GLFWBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Instanced Rendering"))
	{
		return 1;
	}

	App1 *pApp = new App1();
	pApp->Init();

	pApp->Run();

	GLFWBackendTerminate();

	delete pApp;

	return 0;
}