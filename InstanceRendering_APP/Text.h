#ifndef TEXT_H
#define TEXT_H

#include<iostream>
#include<map>
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"CameraClass.h"
#include"TextureClass.h"
#include"MeshClass.h"
#include"ShaderManager.h"
#include"FileClass.h"
#include<ft2build.h>
#include<freetype\freetype.h>
#include"Utility.h"

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text
{
public:
	Text(CameraClass *camera);
	~Text();
	void Init();
	void Render();
	void setFPS(int fps);
	void setInstancingMode(InstancingModes mode);
	void setNumberOfModels(int n);
	
private:
	void Text::RenderText(ShaderManager *shader, std::string text, std::string value, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	std::string getEnumName(InstancingModes mode);

private:
	std::map<GLchar, Character> Characters;
	GLuint m_Text_VAO, m_Text_VBO;
	CameraClass* m_pCamera;
	TextureClass* m_pTexture;
	MeshClass* m_ptextMesh;
	ShaderManager* m_ptextShader;
	int m_fps;
	InstancingModes m_instancingMode;
	int m_numModels;
};

#endif

