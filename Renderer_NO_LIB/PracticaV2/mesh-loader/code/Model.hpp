/**
* @file Model.hpp
* @brief Codigo de Model
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <Color_Buffer.hpp>
#include "Entity.hpp"
#include "math.hpp"
#include "Rasterizer.hpp"
#include "Camera.hpp"
#include <vector>
#include <string>

using std::vector;
using std::string;
using argb::Rgb888;
using argb::Color_Buffer;

namespace render_engine
{

	class Model : public Entity
	{
	private:

		typedef Rgb888                Color;
		typedef Color_Buffer< Color > Color_Buffer;
		typedef Point4f               Vertex;
		typedef vector< Vertex >      Vertex_Buffer;
		typedef vector< int    >      Index_Buffer;
		typedef vector< Color  >      Vertex_Colors;

		// Buffers
		Vertex_Buffer     original_vertices;
		Index_Buffer      original_indices;
		Vertex_Colors     original_colors;
		Vertex_Buffer     transformed_vertices;
		vector< Point4i > display_vertices;

		// Ilumnación
		vector< glm::vec3 > original_normals;
		vector< glm::vec3 > transformed_normals;

	public:

		/**
		* @brief Constructor de Model
		* @param model_path es la ruta del modelo a cargar
		* @param n_mesh es el numero de la mesh del objecto (Para objetos con múltiples meshes)
		* @param mesh_color es el color de los vértices de dicho trozo de mesh
		*/
		Model(const string & model_path, int n_mesh, glm::vec3 mesh_color);

		void update();

		/**
		* @brief Esta funcion se encarga de renderizar, los detalles paso a paso estan dentro del codigo de la funcion
		* @param rasterizer es un objeto de tipo Rasterizer< Color_Buffer >
		* @param camera es un objeto de tipo Camara
		*/
		void render(Rasterizer< Color_Buffer >& rasterizer, const Camera& camera);

		void process_vertexes(size_t number);
		void process_colors(size_t number);
		void process_indexes(size_t number);

	private:

		/**
		* @brief Esta funcion se encarga de cortar las backfaces del objeto para optimizar rendimiento
		* @param projected_vertices es la cadena de vertices proporcionada
		* @param indices es los indices de dichos vertices
		*/
		bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
		float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }
	};

}