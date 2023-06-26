/**
* @file Texture.cpp
* @brief Implementación de Texture
* @author TheCherno
*/

// Copyright (c) 2023 The Cherno
// 2018.01 - 2018.2

#include "Texture.h"
#include "stb_image.h"

namespace example 
{
	/// <summary>
	/// Constructor de Textura que requiere un path de textura
	/// </summary>
	/// <param name="path"></param>
	Texture::Texture(const std::string& path) : path(path),
		local_buffer(nullptr), width(0), height(0), channels_in_file(0)
	{
		// Flipea la textura verticalmente
		stbi_set_flip_vertically_on_load(1);
		local_buffer = stbi_load(path.c_str(), &width, &height, &channels_in_file, 4);

		// Se generan y bindea 1 textura en el hueco render_id
		glGenTextures(1, &render_id);
		glBindTexture(GL_TEXTURE_2D, render_id);

		// Se le establecen los parámetros para que la imagen escale correctamente
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		if (local_buffer) stbi_image_free(local_buffer);
	}

	/// <summary>
	/// Destructor de textura
	/// </summary>
	Texture::~Texture()
	{
		glDeleteTextures(1, &render_id);
	}

	/// <summary>
	/// Bindeo de la textura, se le debe proporcionar un slot
	/// </summary>
	/// <param name="slot"></param>
	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, render_id);
	}

	/// <summary>
	/// Desbindea la textura
	/// </summary>
	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
