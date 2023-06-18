#pragma once

#include "Helper.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace example 
{
    class Shaderer
    {
        Helper debugger;

        Shaderer()
        {

        }

        GLuint compile_shaders()
        {
            GLint succeeded = GL_FALSE;

            // Se crean objetos para los shaders:

            GLuint   vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

            // Se carga el c�digo de los shaders:

            const char* vertex_shaders_code[] = { vertex_shader_code.c_str() };
            const char* fragment_shaders_code[] = { fragment_shader_code.c_str() };
            const GLint    vertex_shaders_size[] = { (GLint)vertex_shader_code.size() };
            const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size() };

            glShaderSource(vertex_shader_id, 1, vertex_shaders_code, vertex_shaders_size);
            glShaderSource(fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

            // Se compilan los shaders:

            glCompileShader(vertex_shader_id);
            glCompileShader(fragment_shader_id);

            // Se comprueba que si la compilaci�n ha tenido �xito:

            glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
            if (!succeeded) debugger.show_compilation_error(vertex_shader_id);

            glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
            if (!succeeded) debugger.show_compilation_error(fragment_shader_id);

            // Se crea un objeto para un programa:

            GLuint program_id = glCreateProgram();

            // Se cargan los shaders compilados en el programa:

            glAttachShader(program_id, vertex_shader_id);
            glAttachShader(program_id, fragment_shader_id);

            // Se linkan los shaders:

            glLinkProgram(program_id);

            // Se comprueba si el linkage ha tenido �xito:

            glGetProgramiv(program_id, GL_LINK_STATUS, &succeeded);
            if (!succeeded) debugger.show_linkage_error(program_id);

            // Se liberan los shaders compilados una vez se han linkado:

            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);

            return (program_id);
        }
    };
}