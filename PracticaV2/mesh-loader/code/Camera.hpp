// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

/*
	#include "Entity.hpp"
	#include "math.hpp"

	class Camera : public Entity
	{
		float FOV;
		float aspect_ratio;
		float near_distance;
		unsigned width;
		unsigned height;

		glm::mat4 projection;

	public:

		Camera::Camera(float given_FOV, float given_near_distance, unsigned width, unsigned height) : width(width), height(height)
		{
			FOV = given_FOV;
			aspect_ratio = 1;
			near_distance = given_near_distance;
		}

		//fov, aspect_ratio, near_d, far_d
		glm::mat4 set_projection_matrix(float FOV, float aspect_ratio, float near_distance)
		{
			// A + alto el primer numero diferente FOV (1 ya es muy lejos, jugar con decimales hasta 21 si se juega con ello)
			// projection = perspective(20.6f, 1, 15, float(width) / height);
			projection = perspective(FOV, aspect_ratio, near_distance, float(width) / height);
		}

		glm::mat4 get_projection_matrix() const
		{
			return projection;
		}

		glm::mat4 get_transform_matrix_inverse() const
		{
			return glm::inverse(get_transform_matrix());
		}
	};
*/

