
// Copyright (c) 2023 Arturo

#pragma once

#include <Color_Buffer.hpp>
#include "Entity.hpp"
#include "math.hpp"
#include "Rasterizer.hpp"
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


		Vertex_Buffer     original_vertices;
		Index_Buffer      original_indices;
		Vertex_Colors     original_colors;
		Vertex_Buffer     transformed_vertices;
		vector< Point4i > display_vertices;

		float angle = 0.f;
		float scale = 0.3f;
		Vector3f position{ 0.f, 0.5f, -10.f };

	public:

		Model(const string & model_path);

		void set_position(const glm::vec3 & new_position)
		{
			position = new_position;
		}

		void update();
		void render(Rasterizer< Color_Buffer > & rasterizer, const Matrix44 & projection, unsigned width, unsigned height);

	private:

		bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
		float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }
	};

}