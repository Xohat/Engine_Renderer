/**
* @file Entity.hpp
* @brief Codigo de Entity, encargado de ser una manera sencilla y genérica de controlar los elementos
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#pragma once

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include <vector>

namespace example
{
	/// <summary>
	/// Codigo de Entity, encargado de ser una manera sencilla y genérica de controlar los elementos
	/// </summary>
	class Entity
	{

	protected:

		///Escala del objeto por defecto en 1.f
		float scale = 1.f;

		///Rotacion alrededor del eje y
		float rotation_y = 0;
		glm::vec3 position = { 0, 0, 0 };

		/// parent esta incializado de base a nullptr para que 
		/// el puntero no apunte a algo aleatorio si no se asigna
		Entity* parent = nullptr;

	public:

		// Setters

		/**
		* @brief Esta funcion settea la entidad de tipo padre
		* @param given_parent es una variable que significa si la entidad en cuestion tiene un padre, por defecto esta setteado a nullptr para evadir falsos positivos
		*/
		void set_parent(Entity& given_parent)
		{
			parent = &given_parent;
		}
		void set_position(const glm::vec3& new_position)
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

		// Getters

		glm::vec3 get_position() const
		{
			return position;
		}

		/**
		* @brief Esta funcion devuelve la transform matrix, esto se usa principalmente para hacer una transform matrix basada
		* en la de el padre si lo hay, asi pudiendo hacer movimientos en coordenadas relativas a dicho parent
		*/
		glm::mat4 get_transform_matrix() const
		{
			glm::mat4 identity(1);
			glm::mat4 scaling = glm::scale(identity, glm::vec3(scale, scale, scale));
			glm::mat4 rotation = glm::rotate(identity, rotation_y, glm::vec3(0.f, 1.f, 0.f));
			glm::mat4 translation = translate(identity, position);								//< X, Y, Z axises distance (Arriba izquierda es el 0,0)

			glm::mat4 transform_matrix = translation * rotation * scaling;

			if (parent != nullptr)
			{
				return parent->get_transform_matrix() * transform_matrix;
			}

			// Creación de la matriz de transformación unificada:
			else return transform_matrix;
		}

		/**
		* @brief Esta funcion incrementa la posicion actual en base a la nueva recibida,
		* se usa principalmente en la cámara
		*/
		void move_position(const glm::vec3& delta_position)
		{
			position += delta_position;
		}
	};
}
