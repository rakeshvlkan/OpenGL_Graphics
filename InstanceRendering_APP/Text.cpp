#include "Text.h"

template <typename T>
std::string tostring(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
};

Text::Text(CameraClass *camera)
{
	m_ptextShader = new ShaderManager();
	m_pCamera = camera;
	m_pTexture = NULL;	
}

Text::~Text()
{
}

void Text::Init()
{   
	m_pTexture = new TextureClass();
	m_ptextShader->AddShaders("text.vs", "text.fs");
	//Text rendering
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, "../fonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

std::string Text::getEnumName(InstancingModes mode)
{
	switch (mode)
	{
	case No_Instancing:
		return "NO_Instancing";
		break;
	case Shader_Instancing:
		return "Shader_Instancing";
		break;
	case Hardware_Instancing:
		return "Hardware_Instancing";
		break;
	default:
		break;
	}
}

void Text::RenderText(ShaderManager *shader, std::string text, std::string value, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	shader->use();
	glUniform3f(glGetUniformLocation(shader->getID(), "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_Text_VAO);
	std::string tempString = text.append(value);
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_Text_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::Render()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Text render

	glm::mat4 Tex_projection = m_pCamera->getOrthographicProjection();
	m_ptextShader->use();
	glUniformMatrix4fv(glGetUniformLocation(m_ptextShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(Tex_projection));

	glGenVertexArrays(1, &m_Text_VAO);
	glGenBuffers(1, &m_Text_VBO);
	glBindVertexArray(m_Text_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_Text_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	RenderText(m_ptextShader, "FPS:", tostring(m_fps), 1700, 1100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "Total Number Of Models :", tostring(m_numModels), 5, 1150, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "CurrentInstancingMode:", tostring(getEnumName(m_instancingMode)), 5, 1110, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "NoInstaning:Press N ", "", 5, 1070, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "HardwareInstancing:Press H ", "", 5, 1030, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "Blinn Light:Press B ", "", 5, 990, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	RenderText(m_ptextShader, "Camera Movements:Press W, S, A, D ", "", 5, 950, 0.6, glm::vec3(1.0f, 0.0f, 0.0f));
	
	glDisable(GL_CULL_FACE);
}

void Text::setFPS(int fps)
{
	m_fps = fps;
}

void Text::setInstancingMode(InstancingModes mode)
{  
	m_instancingMode = mode;
}

void Text::setNumberOfModels(int n)
{ 
	m_numModels = n;
}
