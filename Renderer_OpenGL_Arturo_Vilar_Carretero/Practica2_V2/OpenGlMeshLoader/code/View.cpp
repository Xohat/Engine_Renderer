/**
* @file View.cpp
* @brief Implementacion de View.hpp
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#include "View.hpp"

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

using namespace std;
using namespace glm;

namespace example
{
    View::View(int width, int height)
    :
        angle(0), camera(20.f, 1, 5000.f, width, height), test_tex("../../code/resources/texture/test_tex_2.png"), test_tex_2("../../code/resources/texture/test_tex_1.jpg"), test_displace_tex("../../code/resources/texture/disp_tex_1.png")
    {

        // Se establece la configuración básica:

        glEnable     (GL_CULL_FACE);
        glEnable     (GL_DEPTH_TEST);
        glClearColor (.1f, .1f, .1f, 1.f);      

        // Se compilan y se activan los shaders:

        GLuint program_id = shader.compile_shaders ();
        glUseProgram (program_id);

        model_view_matrix_id = glGetUniformLocation (program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation (program_id, "projection_matrix");

        resize (width, height);

        camera.set_position({ 0,0,0 });

        // Bindeo de textura de hierba
        test_tex.Bind(0);
        // Bindeo de textura metal
        test_tex_2.Bind(2);
        // Bindeo de textura de elevación
        test_displace_tex.Bind(1);

        // Objeto básio drawer
        test_model.get_mesh()->load_mesh("../../assets/Drawers_2.obj");
        test_model.set_position({ -2.f, 0.f, -5.f });
        test_model.set_scale({ 0.5f });

        // Plano de elevación
        test_model_2.get_mesh()->load_mesh("../../assets/plane_2.obj");
        test_model_2.set_position({ 2.f, -1.f, -5.f });

        add_model("Modelo_1", &test_model);
        add_model("Modelo_2", &test_model_2);
    }

    View::~View()
    {
        //test_model.get_mesh()->~Mesh();
        //test_model_2.get_mesh()->~Mesh();
    }

    void View::update ()
    {
        angle += 0.01f;
        test_model.set_angle(angle);
        test_model_2.set_angle(angle);
    }

    void View::render ()
    {
        //DEBIDO A LA IMPLEMENTACIÖN DE LA DISCPLACEMENT TEXTURE HE SIDO FORZADO A PONERLO AQUI

        //------------------------------PRIMERA MALLA----------------------------------------------------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Model* model = models["Modelo_1"];

        glm::vec3 curr_position = model->get_position();

        // Se rota el malla y se empuja hacia el fondo:
        glm::mat4 model_view_matrix(1);

        // Se aplican las transforamciones a la model_view_matrix
        model_view_matrix = glm::translate(model_view_matrix, curr_position);
        model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(0.f, 1.f, 0.f));
        model_view_matrix = camera.get_transform_matrix_inverse() * model_view_matrix;

        // Se settea el valor de la textura en el shader para samplear
        glUniform1i(shader.GetUniformLocation("u_Texture"), 2);
        // Se settea el valor de la textura en el shader para samplear
        glUniform1i(shader.GetUniformLocation("is_displacement"), false);
        // Se settea la model_view_matrix en el shader
        glUniformMatrix4fv(shader.GetUniformLocation("model_view_matrix"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        // Se dibuja la malla:
        glBindVertexArray(model->get_mesh()->get_vao_id());
        glDrawElements(GL_TRIANGLES, model->get_mesh()->get_number_of_indices(), GL_UNSIGNED_SHORT, 0);

        //------------------------------SEGUNDA MALLA----------------------------------------------------

        model = models["Modelo_2"];

        curr_position = model->get_position();

        // Se rota el malla y se empuja hacia el fondo:
        model_view_matrix = glm::mat4(1);

        // Se aplican las transforamciones a la model_view_matrix
        model_view_matrix = glm::translate(model_view_matrix, curr_position);
        model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(0.f, 1.f, 0.f));
        model_view_matrix = camera.get_transform_matrix_inverse() * model_view_matrix;

        // Se settea el valor de la textura en el shader para samplear
        glUniform1i(shader.GetUniformLocation("u_Texture"), 0);
        // Se settea el valor de la textura en el shader para samplear
        glUniform1i(shader.GetUniformLocation("displacement_texture"), 1);
        // Se settea el valor de la textura en el shader para samplear
        glUniform1i(shader.GetUniformLocation("is_displacement"), true);
        // Se settea el valor de la textura en el shader para samplear
        glUniform1f(shader.GetUniformLocation("displacement_up"), 5.f);
        
        // Se settea la model_view_matrix en el shader
        glUniformMatrix4fv(shader.GetUniformLocation("model_view_matrix"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        // Se dibuja la malla:
        glBindVertexArray(model->get_mesh()->get_vao_id());
        glDrawElements(GL_TRIANGLES, model->get_mesh()->get_number_of_indices(), GL_UNSIGNED_SHORT, 0);
    }

    void View::resize (int width, int height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(camera.get_projection_matrix()));

        glViewport (0, 0, width, height);
    }
}
