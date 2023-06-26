/**
* @file Helper.h
* @brief Clase encargada de comprobar errores de opengl, ya que nos dificiles de ver si no se hace esto
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>

using std::string;
using std::cerr;
using std::endl;

// Macro de TheCherno enfocada para pdoer facilitar el proceso de debug
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace example 
{
	/// <summary>
	/// Clase encargada de comprobar errores de opengl, ya que nos dificiles de ver si no se hace esto
	/// </summary>
	class Helper
	{

	public:

		/// <summary>
		/// Función para los errores de compilación
		/// </summary>
		/// <param name="shader_id"></param>
		void   show_compilation_error(GLuint  shader_id);
		/// <summary>
		/// Función para los errores de linkage
		/// </summary>
		/// <param name="program_id"></param>
		void   show_linkage_error(GLuint program_id);
	};
}