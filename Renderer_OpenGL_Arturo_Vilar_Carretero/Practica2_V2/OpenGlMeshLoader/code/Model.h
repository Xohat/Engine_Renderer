/**
* @file Model.h
* @brief Clase encargada de hacer un modelo, usando un objeto de mesh que es por asi decirlo la textura del modelo
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#pragma once

#include "Helper.h"
#include "Mesh.h"
#include "Entity.h"

#include <glad/glad.h>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example 
{
    /// <summary>
    /// Clase encargada de hacer un modelo, usando un objeto de mesh que es por asi decirlo la textura del modelo
    /// </summary>
    class Model : public Entity
    {
        Helper  debugger;
        Mesh    mesh;

        float   angle;

    public:

        Model() : angle(0)
        {

        }

        /// <summary>
        /// Configura el ángulo del modelo
        /// </summary>
        /// <param name="new_angle"></param>
        void set_angle(float new_angle)
        {
            angle = new_angle;
        }
        /// <summary>
        /// Getter de mesh
        /// </summary>
        /// <returns></returns>
        Mesh* get_mesh()
        {
            return &mesh;
        }
        /// <summary>
        /// Getter de la matriz de model view
        /// </summary>
        /// <returns></returns>
        glm::mat4 get_model_view_matrix()
        {
            return get_transform_matrix();
        }
    };
}