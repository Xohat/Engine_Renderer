#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>

using std::string;
using std::cerr;
using std::endl;

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace example 
{
	class Helper
	{

	public:

		void   show_compilation_error(GLuint  shader_id);
		void   show_linkage_error(GLuint program_id);
	};
}