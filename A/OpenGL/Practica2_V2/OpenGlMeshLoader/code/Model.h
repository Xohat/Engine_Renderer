#pragma once

#include "Helper.h"
#include "Mesh.h"

#include <glad/glad.h>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example 
{
    class Model
    {
        Model() : angle(0)
        {

        }

        Helper  debugger;
        Mesh    mesh;

        float   angle;

        void load_mesh(const std::string& mesh_file_path);

        void render();
    };
}