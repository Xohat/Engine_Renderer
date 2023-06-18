
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <string>

    namespace example
    {
        using glm::vec3;

        class View
        {
        private:

            enum
            {
                COORDINATES_VBO,
                COLORS_VBO,
                INDICES_EBO,
                VBO_COUNT
            };

            //Shaderer
            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLuint  vbo_ids[VBO_COUNT];
            GLuint  vao_id;

            GLsizei number_of_indices;

            GLint   model_view_matrix_id;
            GLint   projection_matrix_id;

            float   angle;

        public:

            View(int width, int height);
           ~View();

           //View
            void   update ();

            //Mesh
            void   render ();

            //Camera?
            void   resize (int width, int height);

        private:

            //Shaderer
            GLuint compile_shaders        ();

            //Helper
            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);

            //Mesh
            void   load_mesh              (const std::string & mesh_file_path);
            vec3   random_color           ();
        };
    }
#endif
