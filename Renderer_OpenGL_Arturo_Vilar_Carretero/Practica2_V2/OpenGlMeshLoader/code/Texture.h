/**
* @file Texture.h
* @brief Código encargado del manejo de texturas
* @author TheCherno
*/

// Copyright (c) 2023 The Cherno
// 2018.01 - 2018.2

#include "Helper.h"

#pragma once

namespace example 
{
	/// <summary>
	/// Código encargado del manejo de texturas
	/// </summary>
	class Texture
	{
		/// <summary>
		/// Helper para debug
		/// </summary>
		Helper helper;
		/// <summary>
		/// Render ID
		/// </summary>
		unsigned int render_id;
		/// <summary>
		/// Path para la textura
		/// </summary>
		std::string path;
		/// <summary>
		/// Buffer local para la carga de la imagen
		/// </summary>
		unsigned char* local_buffer;

		// Propiedades de la textura en si

		/// <summary>
		/// Canales de la textura, alpha, emisivo, etc
		/// </summary>
		int channels_in_file;
		/// <summary>
		/// Width de la textura
		/// </summary>
		int width;
		/// <summary>
		/// Height de la textura
		/// </summary>
		int height;

	public:

		/// <summary>
		/// Constructor de Textura que requiere un path de textura
		/// </summary>
		/// <param name="path"></param>
		Texture(const std::string& path);
		/// <summary>
		/// Destructor de textura
		/// </summary>
		~Texture();

		/// <summary>
		/// Bindeo de la textura, se le debe proporcionar un slot
		/// </summary>
		/// <param name="slot"></param>
		void Bind(unsigned int slot = 0) const;

		/// <summary>
		/// Desbindea la textura
		/// </summary>
		void Unbind() const;

		/// <summary>
		/// Getter de Width de la textura
		/// </summary>
		/// <returns></returns>
		inline int get_width() const { return width; }

		/// <summary>
		/// Getter de height de la textura
		/// </summary>
		/// <returns></returns>
		inline int get_height() const { return height; }
	};
}
