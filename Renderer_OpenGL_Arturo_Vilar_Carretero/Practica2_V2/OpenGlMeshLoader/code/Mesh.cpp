/**
* @file Mesh.cpp
* @brief Implementacion de la reación de una mesh por opengl
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.05 - 2023.06

#include "Mesh.h"

namespace example 
{
	void Mesh::load_mesh(const std::string& mesh_file_path)
	{
        Assimp::Importer importer;

        auto scene = importer.ReadFile
        (
            mesh_file_path,
            aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
        );

        // Si scene es un puntero nulo significa que el archivo no se pudo cargar con éxito:

        if (scene && scene->mNumMeshes > 0)
        {
            // Para este ejemplo se coge la primera malla solamente:

            auto mesh = scene->mMeshes[0];

            size_t number_of_vertices = mesh->mNumVertices;

            // Se generan índices para los VBOs del cubo:

            glGenBuffers(VBO_COUNT, vbo_ids);
            glGenVertexArrays(1, &vao_id);

            // Se activa el VAO del cubo para configurarlo:

            glBindVertexArray(vao_id);

            // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

            static_assert(sizeof(aiVector3D) == sizeof(fvec3), "aiVector3D should composed of three floats");

            glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);

            glBufferData(GL_ARRAY_BUFFER, number_of_vertices * sizeof(aiVector3D), mesh->mVertices, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            // Se suben a un VBO los datos de color y se vinculan al VAO:

            glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[UVS_VBO]);

            if (&mesh->mTextureCoords[0] != nullptr) 
            {
				std::vector<vec2> uvs(number_of_vertices);

				for (int i = 0; i < number_of_vertices; ++i)
				{
					uvs[i].x = mesh->mTextureCoords[0][i].x;
					uvs[i].y = mesh->mTextureCoords[0][i].y;
				}

                glBufferData(GL_ARRAY_BUFFER, number_of_vertices * sizeof(vec2), uvs.data (), GL_STATIC_DRAW);

                glEnableVertexAttribArray(1);

                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
            }

            // Los índices en ASSIMP están repartidos en "faces", pero OpenGL necesita un array de enteros
            // por lo que vamos a mover los índices de las "faces" a un array de enteros:

            // Se asume que todas las "faces" son triángulos (revisar el flag aiProcess_Triangulate arriba).

            number_of_indices = (unsigned int)mesh->mNumFaces * 3;

            vector< GLshort > indices(number_of_indices);

            auto vertex_index = indices.begin();

            for (unsigned i = 0; i < mesh->mNumFaces; ++i)
            {
                auto& face = mesh->mFaces[i];

                assert(face.mNumIndices == 3);

                *vertex_index++ = face.mIndices[0];
                *vertex_index++ = face.mIndices[1];
                *vertex_index++ = face.mIndices[2];
            }

            // Se suben a un EBO los datos de índices:

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_EBO]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLshort), indices.data(), GL_STATIC_DRAW);
        };
    }

    vec3 Mesh::random_color()
    {
        return vec3
        (
            float(rand()) / float(RAND_MAX),
            float(rand()) / float(RAND_MAX),
            float(rand()) / float(RAND_MAX)
        );
    }
}