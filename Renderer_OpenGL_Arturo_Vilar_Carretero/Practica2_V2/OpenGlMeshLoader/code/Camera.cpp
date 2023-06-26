/**
* @file Camera.cpp
* @brief Implementacion de Camera
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#include "Camera.h"

namespace example
{
	/// <summary>
	/// Constructor de Camera
	/// </summary>
	/// <param name="given_FOV"></param>
	/// <param name="given_near_distance"></param>
	/// <param name="given_far_distance"></param>
	/// <param name="given_width"></param>
	/// <param name="given_height"></param>
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
	};
}