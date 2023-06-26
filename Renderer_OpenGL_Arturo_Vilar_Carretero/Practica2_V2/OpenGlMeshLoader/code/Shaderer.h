/**
* @file Shaderer.h
* @brief Clase encargada de cargar shaders
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#pragma once

#include "Helper.h"
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace example 
{
    // Struct creado para poder devolver dos datos con un solo return (Autor: TheCherno)
    struct shader_code 
    {
        std::string vertex_code;
        std::string fragment_code;
    };

    // Carga de meshes desde un archivo (Autor TheCherno)
    static shader_code parse_shader(const::std::string& path)
    {
        // Carga el archivo
        std::ifstream stream(path);
        
        // Tipo de shader (Tener en cuenta los valores del enum)
        enum class shader_type 
        {
            NONE        = -1, 
            VERTEX      = 0, 
            FRAGMENT    = 1
        };

        // Línea a analizar ahora
        std::string line;

        // Array que se va a a devolver
            // Hueco 0: Vertex shader
            // Hueco 1: Fragment shader
        std::stringstream return_stream[2];
        shader_type type = shader_type::NONE;

        // Revisa todo el documento viendo todo el archivo por stream y leyendo línea por línea
        while (getline(stream, line)) 
        {
            // Por esto la sintaxis de los shaders debe ser
                // #shader vertex
                // #shader fragment
            // Ya que primero encuentra las líneas que tengan shader y tras eso la palabra clave vertex o fragment
            if (line.find("#shader") != std::string::npos) 
            {
                // Si encuentra una línea tras vertex la introduce en el 
                // hueco de shader_type::VERTEX que al ser un enum tiene valor de 0
                if (line.find("vertex") != std::string::npos) 
                {
                    type = shader_type::VERTEX;
                }
                // Si encuentra una línea tras fragment la introduce en el 
                // hueco de shader_type::fragment que al ser un enum tiene valor de 1
                else if (line.find("fragment") != std::string::npos) 
                {
                    type = shader_type::FRAGMENT;
                }
            }
            else 
            {
                // Si la línea no tiene ninguna de las dos marcas se supone que es el código 
                // correspondietne antes de entrar en el siguiente fragment maracdo por el line.find()
                return_stream[(int)type] << line << '\n';
            }
        }

        // Tras acabar de cargar el array se devuelven los datos en el formato de un struct shader_code
        return { return_stream[0].str(), return_stream[1].str() };
    }

    /// <summary>
    /// Clase encargada de cargar shaders
    /// </summary>
    class Shaderer
    {
        Helper debugger;

        shader_code source;

        GLuint current_program_id;

    public:

        /// <summary>
        /// Constructor de Shaderer, por si requiere añadirse alguna configuración inicial de los valores o no
        /// </summary>
        Shaderer()
        {

        }

        /// <summary>
        /// Compila los shaders
        /// </summary>
        /// <returns></returns>
        GLuint compile_shaders()
        {
            // Carga el shader desde el archivo
            source = parse_shader("../../code/resources/shader/BasicShader.shader");

            GLint succeeded = GL_FALSE;

            // Se crean objetos para los shaders:

            GLuint   vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

            const char* vertex_shaders_code[] = { source.vertex_code.c_str() };
            const char* fragment_shaders_code[] = { source.fragment_code.c_str() };
            const GLint    vertex_shaders_size[] = { (GLint)source.vertex_code.size() };
            const GLint  fragment_shaders_size[] = { (GLint)source.fragment_code.size() };

            glShaderSource(vertex_shader_id, 1, vertex_shaders_code, vertex_shaders_size);
            glShaderSource(fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

            // Se compilan los shaders:

            glCompileShader(vertex_shader_id);
            glCompileShader(fragment_shader_id);

            // Se comprueba que si la compilación ha tenido éxito:

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

            // Se comprueba si el linkage ha tenido éxito:

            glGetProgramiv(program_id, GL_LINK_STATUS, &succeeded);
            if (!succeeded) debugger.show_linkage_error(program_id);

            // Se liberan los shaders compilados una vez se han linkado:

            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);

            current_program_id = program_id;

            return (program_id);
        }

        /// <summary>
        /// Función enfocada a localizar los uniforms dentro de un shader
        /// para esto se ha guardado la current_program_id
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        GLuint GetUniformLocation(const std::string& name)
        {
            GLuint location = glGetUniformLocation(current_program_id, name.c_str());
            if (location == -1) std::cout << "Warning: uniform '" << name << "' doesnt exist!" << std::endl;

            return location;
        }
    };
}