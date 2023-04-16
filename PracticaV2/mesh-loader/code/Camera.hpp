/**
* @file Camera.hpp
* @brief Codigo de Camera
* @author Arturo Vilar Carretero
*/

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

		float FOV;				///Field of view
		float near_distance;	///Near distance
		float far_distance;		///Far distance 
		unsigned width;			///Window width
		unsigned height;		///Window height

	public:

		Camera::Camera(float given_FOV, float given_near_distance, float given_far_distance, unsigned given_width, unsigned given_height);

		// Getters
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
		glm::mat4 get_transform_matrix_inverse() const //< Movimiento en el eje inverso al de la cámara
		{
			return glm::inverse(get_transform_matrix());
		}

		// Setters
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

		/**
		* @brief Esta función se encarga de refrescar la matriz de proyección, 
		* esto se debe hacer cuando se modifiquen los valores de FOV, near_distance, far_distance, width o height
		*/
		void refresh_projection_matrix() 
		{
			projection = perspective(FOV, near_distance, far_distance, float(width) / height);
		}
	};
}
