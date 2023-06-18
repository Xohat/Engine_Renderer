#include "Model.h"

namespace example 
{
    void Model::load_mesh(const std::string& mesh_file_path)
    {
        mesh.load_mesh(mesh_file_path);
    }

    void Model::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Se rota el malla y se empuja hacia el fondo:

        glm::mat4 model_view_matrix(1);

        model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, -3.f));
        model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(0.f, 1.f, 0.f));

        glUniformMatrix4fv(mesh.get_model_view_matrix_id(), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        // Se dibuja la malla:

        glBindVertexArray(mesh.get_vao_id());
        glDrawElements(GL_TRIANGLES, mesh.get_number_of_indices(), GL_UNSIGNED_SHORT, 0);
    }
}