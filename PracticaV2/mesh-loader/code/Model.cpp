
// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// Basado en c�digo de �ngel
// 2023.03 - 2023.04

#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace render_engine
{

	Model::Model(const string& model_path)
	{
		Assimp::Importer importer;

		auto scene = importer.ReadFile
		(
			model_path,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
		);

		// Si scene es un puntero nulo significa que el archivo no se pudo cargar con �xito:

		if (scene && scene->mNumMeshes > 0)
		{
			/* 
				if (scene->mNumMeshes > 1) 
				{
					for (int i = 0; i < scene->mNumMeshes; i++)
					{
						 compound_meshes.push_back(*scene->mMeshes[i]);

						 process_mesh(&compound_meshes[i]);
					}
				}
				else 
				{
					// Para este ejemplo se coge la primera malla solamente:

					process_mesh(scene->mMeshes[0]);
				}
			*/

			// Se define el n�mero de v�rtices de la mesh enviada

//size_t number_of_vertices = mesh->mNumVertices;

			size_t numbers_of_vertices = 0;

			for (int i = 0; i < 1; ++i)
			{
				numbers_of_vertices += scene->mMeshes[i]->mNumVertices;
			}

			// Se copian los datos de coordenadas de v�rtices:

			original_vertices.resize(numbers_of_vertices);

			size_t merged_mesh_vertex_index = 0;

			for (int mesh_index = 0; mesh_index < 1; ++mesh_index)
			{
				auto& mesh = scene->mMeshes[mesh_index];

				for (size_t index = 0; index < numbers_of_vertices; index++)
				{
					auto& vertex = mesh->mVertices[index];

					original_vertices[merged_mesh_vertex_index] = Vertex(vertex.x, -vertex.z, vertex.y, 1.f);
				}
			}


			transformed_vertices.resize(numbers_of_vertices);
			display_vertices.resize(numbers_of_vertices);

			// Se inicializan los datos de color de los v�rtices con colores aleatorios:

			original_colors.resize(numbers_of_vertices);

			for (size_t index = 0; index < numbers_of_vertices; index++)
			{
				original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
			}

			// Se generan los �ndices de los tri�ngulos:

			size_t number_of_triangles = 0;

			for (int i = 0; i < 1; ++i)
			{
				number_of_triangles += scene->mMeshes[i]->mNumFaces;
			}

			original_indices.resize(number_of_triangles * 3);

			Index_Buffer::iterator indices_iterator = original_indices.begin();

			size_t previous_vertices_count = 0;

			for (int mesh_index = 0; mesh_index < 1; ++mesh_index)
			{
				auto& mesh = scene->mMeshes[mesh_index];

				for (size_t index = 0; index < mesh->mNumFaces; index++)
				{
					auto& face = mesh->mFaces[index];

					assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 �ndices,
																// pero nos interesa que solo haya tri�ngulos
					auto indices = face.mIndices;

					*indices_iterator++ =  int(indices[0]);
					*indices_iterator++ =  int(indices[1]);
					*indices_iterator++ = int(indices[2]);
				}

				previous_vertices_count += mesh->mNumVertices;
			}
		}
	}

	/*
		void Model::process_mesh(aiMesh* mesh, aiScene* scene) 
		{

		}
	*/

	void Model::update()
	{
		//Para la rotaci�n de la misma
		angle += 0.025f;
	}

	void Model::render(Rasterizer< Color_Buffer >& rasterizer, const Matrix44 & projection, unsigned width, unsigned height)
	{
		Matrix44 identity(1);

		// Creaci�n de la matriz de transformaci�n unificada:
		Matrix44 transformation = projection * get_transform_matrix(scale, angle, position);

		// Se transforman todos los v�rtices usando la matriz de transformaci�n resultante:

		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			// Se multiplican todos los v�rtices originales con la matriz de transformaci�n y
			// se guarda el resultado en otro vertex buffer:

			Vertex& vertex = transformed_vertices[index] = transformation * original_vertices[index];

			// La matriz de proyecci�n en perspectiva hace que el �ltimo componente del vector
			// transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

			float divisor = 1.f / vertex.w;

			vertex.x *= divisor;
			vertex.y *= divisor;
			vertex.z *= divisor;
			vertex.w = 1.f;
		}

		// Se convierten las coordenadas transformadas y proyectadas a coordenadas
		// de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
		// La coordenada Z se escala a un valor suficientemente grande dentro del
		// rango de int (que es lo que espera fill_convex_polygon_z_buffer).

		scaling = glm::scale(identity, glm::vec3(float(width / 2), float(height / 2), 100000000.f));
		translation = translate(identity, Vector3f{ float(width / 2), float(height / 2), 0.f });
		transformation = translation * scaling;

		for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
		{
			display_vertices[index] = Point4i(transformation * transformed_vertices[index]);
		}

		for (int* indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
		{
			if (not is_frontface(transformed_vertices.data(), indices))
			{
				// Se establece el color del pol�gono a partir del color de su primer v�rtice:

				rasterizer.set_color(original_colors[*indices]);

				// Se rellena el pol�gono:

				rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
			}
		}

	}

	bool Model::is_frontface(const Vertex* const projected_vertices, const int* const indices)
	{
		const Vertex& v0 = projected_vertices[indices[0]];
		const Vertex& v1 = projected_vertices[indices[1]];
		const Vertex& v2 = projected_vertices[indices[2]];

		// Se asumen coordenadas proyectadas y pol�gonos definidos en sentido horario.
		// Se comprueba a qu� lado de la l�nea que pasa por v0 y v1 queda el punto v2:

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
	}
}
