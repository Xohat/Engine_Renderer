// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include "math.hpp"
#include "Entity.hpp"

namespace render_engine 
{
	class Camera : public Entity
	{
		glm::mat4 projection;

		float FOV;
		float near_distance;
		float far_distance;
		unsigned width;
		unsigned height;

	public:

		Camera::Camera(float given_FOV, float given_near_distance, float given_far_distance, unsigned given_width, unsigned given_height)
		{
			FOV = given_FOV;
			near_distance = given_near_distance;
			far_distance = given_far_distance;
			width = given_width;
			height = given_height;
			scale = 1;
			rotation_y = 0;
			position = { 0, 0, 0 };

			//Si cambia FOV / near_distance / width / height solo se actualiza la projection

			refresh_projection_matrix();
		}

		float get_fov() const
		{
			return FOV;
		}

		float get_near_distance() const
		{
			return near_distance;
		}

		float get_far_distance() const
		{
			return far_distance;
		}

		unsigned get_width() const
		{
			return width;
		}

		unsigned get_height() const
		{
			return height;
		}

		glm::mat4 get_projection_matrix() const
		{
			return projection;
		}

		//Movimiento en el eje inverso al de la cámara
		glm::mat4 get_transform_matrix_inverse() const
		{
			return glm::inverse(get_transform_matrix());
		}

		void set_fov(float new_fov) 
		{
			FOV = new_fov;
			refresh_projection_matrix();
		}

		void set_near_distance(float new_near_distance)
		{
			near_distance = new_near_distance;
			refresh_projection_matrix();
		}

		void set_far_distance(float new_far_distance)
		{
			far_distance = new_far_distance;
			refresh_projection_matrix();
		}

	private:

		void refresh_projection_matrix() 
		{
			// A + alto el primer numero diferente FOV (1 ya es muy lejos, jugar con decimales hasta 21 si se juega con ello)
			projection = perspective(FOV, near_distance, far_distance, float(width) / height);
		}
	};
}
