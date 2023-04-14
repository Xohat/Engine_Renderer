
// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// Basado en código de Ángel
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

		// Si scene es un puntero nulo significa que el archivo no se pudo cargar con éxito:

		if (scene && scene->mNumMeshes > 0)
		{
			// Para este ejemplo se coge la primera malla solamente:

			auto mesh = scene->mMeshes[0];

			size_t number_of_vertices = mesh->mNumVertices;

			// Se copian los datos de coordenadas de vértices:

			original_vertices.resize(number_of_vertices);

			for (size_t index = 0; index < number_of_vertices; index++)
			{
				auto& vertex = mesh->mVertices[index];

				original_vertices[index] = Vertex(vertex.x, -vertex.z, vertex.y, 1.f);
			}

			transformed_vertices.resize(number_of_vertices);
			display_vertices.resize(number_of_vertices);

			// Se inicializan los datos de color de los vértices con colores aleatorios:

			original_colors.resize(number_of_vertices);

			for (size_t index = 0; index < number_of_vertices; index++)
			{
				original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
			}

			// Se generan los índices de los triángulos:

			size_t number_of_triangles = mesh->mNumFaces;

			original_indices.resize(number_of_triangles * 3);

			Index_Buffer::iterator indices_iterator = original_indices.begin();

			for (size_t index = 0; index < number_of_triangles; index++)
			{
				auto& face = mesh->mFaces[index];

				assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 índices,
															// pero nos interesa que solo haya triángulos
				auto indices = face.mIndices;

				*indices_iterator++ = int(indices[0]);
				*indices_iterator++ = int(indices[1]);
				*indices_iterator++ = int(indices[2]);
			}
		}

	}

	void Model::update()
	{
		angle += 0.025f;
		set_rotation_y(angle);
	}

	void Model::render(Rasterizer< Color_Buffer >& rasterizer, const Camera & camera)
	{
		// Creación de la matriz de transformación unificada:
		Matrix44 transformation = camera.get_projection_matrix() * camera.get_transform_matrix_inverse() * get_transform_matrix();

		// Se transforman todos los vértices usando la matriz de transformación resultante:

		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			// Se multiplican todos los vértices originales con la matriz de transformación y
			// se guarda el resultado en otro vertex buffer:

			Vertex& vertex = transformed_vertices[index] = transformation * original_vertices[index];

			// La matriz de proyección en perspectiva hace que el último componente del vector
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

		Matrix44 identity(1);

		glm::mat4 scaling = glm::scale(identity, glm::vec3(float(camera.get_width() / 2), float(camera.get_height() / 2), 100000000.f));
		glm::mat4 translation = translate(identity, Vector3f{ float(camera.get_width() / 2), float(camera.get_height() / 2), 0.f });
		transformation = translation * scaling;

		for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
		{
			display_vertices[index] = Point4i(transformation * transformed_vertices[index]);
		}

		for (int* indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
		{
			if (not is_frontface(transformed_vertices.data(), indices))
			{
				// Se establece el color del polígono a partir del color de su primer vértice:

				rasterizer.set_color(original_colors[*indices]);

				// Se rellena el polígono:

				rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
			}
		}

	}

	bool Model::is_frontface(const Vertex* const projected_vertices, const int* const indices)
	{
		const Vertex& v0 = projected_vertices[indices[0]];
		const Vertex& v1 = projected_vertices[indices[1]];
		const Vertex& v2 = projected_vertices[indices[2]];

		// Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
		// Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
	}

}
