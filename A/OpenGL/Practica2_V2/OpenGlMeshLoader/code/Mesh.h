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
	class Mesh 
	{
        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };

        GLuint  vbo_ids[VBO_COUNT];
        GLuint  vao_id;

        GLsizei number_of_indices;

        GLint   model_view_matrix_id;
        GLint   projection_matrix_id;

		vec3 random_color();

	public:

		void load_mesh(const std::string& mesh_file_path);

        GLuint get_vao_id()
        {
            return vao_id;
        }
        GLint get_model_view_matrix_id() 
        {
            return model_view_matrix_id;
        }
        GLint get_projection_matrix_id() 
        {
            return projection_matrix_id;
        }
        GLsizei get_number_of_indices() 
        {
            return number_of_indices;
        }
	};
}