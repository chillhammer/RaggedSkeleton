#include <skelpch.h>
#include "Texture.h"
#include <glad/glad.h>
#include <stb_image/stb_image.h>

namespace Skel
{
	Texture::Texture()
	{
		GLCall(glGenTextures(1, &m_RendererID));

	}
	Texture::Texture(const std::string & path) : m_FilePath(path), m_LocalBuffer(nullptr),
		m_Height(0), m_Width(0), m_BPP(0)
	{
		GLCall(glGenTextures(1, &m_RendererID));
	}

	Texture::Texture(const Texture & other) : m_FilePath(other.m_FilePath), m_LocalBuffer(other.m_LocalBuffer),
		m_Height(other.m_Height), m_Width(other.m_Width), m_BPP(other.m_BPP), m_RendererID(other.m_RendererID)
	{
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_RendererID));
	}

	void Texture::LoadTexture()
	{
		if (m_FilePath == "")
			ASSERT(false, "Cannot load texture with invalid file path");
		this->LoadTexture(m_FilePath);
	}

	void Texture::LoadTexture(const std::string & path)
	{
		m_FilePath = path;
		stbi_set_flip_vertically_on_load(0);
		m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		ASSERT(m_LocalBuffer, "Failed to load texture");

		// Bind
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		// Setting OpenGL Parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		// Unbind and free local buffer
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	}

	void Texture::Bind(unsigned int slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void Texture::Unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
}