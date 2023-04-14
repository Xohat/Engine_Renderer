// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "math.hpp"
#include <vector>

namespace render_engine 
{
	class Entity
	{

	protected:

		float scale = 1.f;
		float rotation_y = 0;			//Rotacion alrededor del eje y
		glm::vec3 position = {0, 0, 0};

		Entity * parent = nullptr;

	public:

		void set_parent(Entity & given_parent) 
		{
			parent = &given_parent;
		}

		void set_position(const glm::vec3 & new_position) 
		{
			position = new_position;
		}

		void set_scale(const float new_scale)
		{
			scale = new_scale;
		}

		void set_rotation_y(float new_rotation_y)
		{
			rotation_y = new_rotation_y;
		}

		void move_position(const glm::vec3& delta_position)
		{
			position += delta_position;
		}


		glm::mat4 get_transform_matrix() const
		{
			glm::mat4 identity(1);
			glm::mat4 scaling = glm::scale(identity, glm::vec3(scale, scale, scale));
			glm::mat4 rotation = rotate_around_y(identity, rotation_y);
			glm::mat4 translation = translate(identity, position);			//< X, Y, Z axises distance (Arriba izquierda es el 0,0)

			glm::mat4 transform_matrix = translation * rotation * scaling;

			if (parent != nullptr)
			{
				return parent->get_transform_matrix() * transform_matrix;
			}

			// Creación de la matriz de transformación unificada:
			else return transform_matrix;
		}
	};
}
