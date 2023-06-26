/**
* @file View.hpp
* @brief Clase encargada de manejar todo el visionado de los elementos, es realmente un concepto similar a una escena
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <string>
    #include "Shaderer.h"
    #include "Helper.h"
    #include "Model.h"
    #include "Camera.h"
    #include "Texture.h"

    #include <map>

    using namespace std;

    namespace example
    {
        using glm::vec3;

        /// <summary>
        /// Clase encargada de manejar todo el visionado de los elementos, es realmente un concepto similar a una escena
        /// </summary>
        class View
        {
        private:

            /// <summary>
            /// Herramientas, shader
            /// </summary>
            Shaderer shader;
            /// <summary>
            /// Herramientas, helper de debug
            /// </summary>
            Helper helper;
            /// <summary>
            /// Herramientas, camara
            /// </summary>
            Camera camera;

            /// <summary>
            /// Texturas
            /// </summary>
            Texture test_tex;
            Texture test_tex_2;
            Texture test_displace_tex;

            /// <summary>
            /// Modelos
            /// </summary>
            Model test_model;
            Model test_model_2;

            GLint   model_view_matrix_id;
            GLint   projection_matrix_id;

            /// <summary>
            /// Ángulo para configurar la rotación de los objetos
            /// </summary>
            float   angle;

            map< string, Model*> models;

            bool is_displacement;

        public:

            View(int width, int height);
           ~View();

            /// <summary>
            /// Este método solo actualiza el ángulo y se lo settea a los modelos
            /// </summary>
            void   update ();
            /// <summary>
            /// Este método se itera por cada uno de los modelos en la escena y renderiza
            /// </summary>
            void   render ();
            /// <summary>
            /// Este método configura la projection matrix
            /// </summary>
            /// <param name="width"></param>
            /// <param name="height"></param>
            void   resize (int width, int height);

            /// <summary>
            /// Getter de camara
            /// </summary>
            /// <returns></returns>
            Camera* get_camera()       
            {
                return &camera;
            }
            /// <summary>
            /// Añade un nuevo modelo a el array de modelos
            /// </summary>
            /// <param name="model_name"></param>
            /// <param name="model_to_add"></param>
            void add_model(string model_name, Model* model_to_add)
            {
                models.insert(std::make_pair(model_name, model_to_add));
            }
            /// <summary>
            /// Getter del mapa de modelos
            /// </summary>
            /// <returns></returns>
            map< string, Model*> get_models() 
            {
                return models;
            }
        };
    }
#endif
