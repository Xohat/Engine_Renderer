#pragma once

#include "math.hpp"
#include <vector>

namespace render_engine 
{
	class Entity
	{
		float scale;
		float rotation;   //Rotacion general
		glm::vec3 position;

	public:

		glm::mat4 get_transform_matrix(float scale, float angle, glm::vec3 position)
		{
			glm::mat4 identity(1);
			glm::mat4 scaling = glm::scale(identity, glm::vec3(scale, scale, scale));
			glm::mat4 rotation_y = rotate_around_y(identity, angle);

			// X, Y, Z axises distance (Arriba izquierda es el 0,0)
			glm::mat4 translation = translate(identity, position);

			// Creación de la matriz de transformación unificada:
			return translation * rotation_y * scaling;
			//return parent.getTransformMatrix * translation * rotation_y * scaling;
		}
	};
}
