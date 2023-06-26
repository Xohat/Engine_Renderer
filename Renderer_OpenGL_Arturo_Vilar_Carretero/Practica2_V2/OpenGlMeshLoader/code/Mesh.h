/**
* @file Mesh.h
* @brief Clase encargada de crear el concepto de Mesh en base a un objeto cargado por ruta
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace glm;
using namespace std;

namespace example 
{
	// Resumen para que un tercero entienda con facilidad el funcionamiento de código
	// Que clases hay para que sirven

	/// <summary>
	/// Clase encargada de crear el concepto de Mesh en base a un objeto cargado por ruta
	/// </summary>
	class Mesh 
	{
        enum
        {
            COORDINATES_VBO,
            UVS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };

        GLuint  vbo_ids[VBO_COUNT];
        GLuint  vao_id;

        unsigned int number_of_indices;

        GLint   model_view_matrix_id;
        GLint   projection_matrix_id;

		vec3 random_color();

	public:

        ~Mesh()
        {
            //glDeleteVertexArrays(1, &vao_id);
            //glDeleteBuffers(VBO_COUNT, vbo_ids);
        }

		void load_mesh(const std::string& mesh_file_path);

        /// <summary>
        /// Getter de vao_id
        /// </summary>
        /// <returns></returns>
        GLuint get_vao_id()
        {
            return vao_id;
        }
        /// <summary>
        /// Getter de la matriz de transformación
        /// </summary>
        /// <returns></returns>
        GLint get_model_view_matrix_id() 
        {
            //++model_view_matrix_id;
            return model_view_matrix_id;
        }
        /// <summary>
        /// Getter de la matriz de proyección
        /// </summary>
        /// <returns></returns>
        GLint get_projection_matrix_id() 
        {
            //++projection_matrix_id;
            return projection_matrix_id;
        }
        /// <summary>
        /// Getter del número de índices
        /// </summary>
        /// <returns></returns>
        GLsizei get_number_of_indices() 
        {
            return number_of_indices;
        }
	};
}