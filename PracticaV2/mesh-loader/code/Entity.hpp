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

		float scale;
		float rotation;			//Rotacion general

		glm::vec3 position;
		glm::mat4 scaling;
		glm::mat4 rotation_y;
		glm::mat4 translation;

		Entity * parent = nullptr;

	public:

		void set_parent(Entity & given_parent) 
		{
			parent = &given_parent;
		}

		glm::mat4 get_transform_matrix(float scale, float angle, glm::vec3 position)
		{
			glm::mat4 identity(1);
			scaling = glm::scale(identity, glm::vec3(scale, scale, scale));
			rotation_y = rotate_around_y(identity, angle);

			// X, Y, Z axises distance (Arriba izquierda es el 0,0)
			translation = translate(identity, position);

			if (parent != nullptr)
			{
				return parent->get_transform_matrix(scale, angle, position) * translation * rotation_y * scaling;
			}

			// Creación de la matriz de transformación unificada:
			else return translation * rotation_y * scaling;
		}
	};
}
