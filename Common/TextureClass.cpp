#include "TextureClass.h"

TextureClass::TextureClass()
{
}

TextureClass::~TextureClass()
{
}

unsigned int TextureClass::GetTextureID()
{
	return m_textureID;
}

std::string TextureClass::GetTextureType()
{
	return m_type;
}

std::string TextureClass::GetTexturePath()
{
	return m_path;
}

void TextureClass::SetTextureID(unsigned int ID)
{
	m_textureID = ID;
}

void TextureClass::SetTextureType(std::string type)
{
	m_type = type;
}

void TextureClass::SetTexturePath(std::string path)
{
	m_path = path;
}

void TextureClass::Bind(unsigned int TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void TextureClass::LoadTexture(char const * path)
{
	glGenTextures(1, &m_textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}


