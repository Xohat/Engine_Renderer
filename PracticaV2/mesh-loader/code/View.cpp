/**
* @file View.cpp
* @brief Implementacion de View
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// Basado en código de Ángel
// 2023.03 - 2023.04

#include <cassert>
#include <cmath>
#include "math.hpp"
#include "View.hpp"
#include "Camera.hpp"


namespace render_engine
{

    View::View(unsigned width, unsigned height)
    :
        color_buffer	(width, height),								//color buffer
        rasterizer		(color_buffer ),								//rasterizer

		floor			(mill_floor_file_path, 0, { 0.7f, 0.4f, 0 }),	//path, n_mesh, color
		floor_grass		(mill_floor_file_path, 1, { 0, 0.9f, 0.1f }),	//path, n_mesh, color

		mill_tree_root	(mill_tree_file_path, 0, { 0.7f, 0.4f, 0 }),	//path, n_mesh, color
		mill_tree_leaf	(mill_tree_file_path, 1, { 0, 0.9f, 0.1f }),	//path, n_mesh, color

		mill_root		(mill_file_path, 0, { 0.f, 0.f, 0.f }),
		mill_root2		(mill_file_path, 1, { 0.38f, 0.33f, 0.28f }),	//path, n_mesh, color
		mill_extras		(mill_file_path, 2, { 0.78f, 0.28f, 0.08f }),	//path, n_mesh, color

		main_camera		(20.6f, 1, 15, width, height)					//FOV, near_distance, far_distance, width, height
    {
		floor.set_position({ 0.f, -2.f, -10.f });

		floor_grass.set_parent(floor);

		mill_tree_root.set_parent(floor_grass);
		mill_tree_root.set_position({ 0.0f, -0.1f, 0.25f });			//movimiento relativo al padre

		mill_tree_leaf.set_parent(mill_tree_root);

		mill_root.set_parent(floor_grass);
		mill_root.set_position({ 0.f, -1.25f, 0.f });					// movimiento relativo al padre
		
		mill_root2.set_parent(mill_root);

		mill_extras.set_parent(mill_root);

		//z --> + = + lejos
		main_camera.set_position({ 0.f, -2.5f, -5.5f });				// posición inicial de la cámara
    }

    void View::update ()
    {
		floor.update();
    }

    void View::render ()
    {
		// Se borra el framebúffer y se dibujan los triángulos:

		rasterizer.clear();

		floor.render(rasterizer, main_camera);
		floor_grass.render(rasterizer, main_camera);

		mill_tree_root.render(rasterizer, main_camera);
		mill_tree_leaf.render(rasterizer, main_camera);

		mill_root.render(rasterizer, main_camera);
		mill_root2.render(rasterizer, main_camera);
		mill_extras.render(rasterizer, main_camera);

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		color_buffer.blit_to_window();
    }


}
