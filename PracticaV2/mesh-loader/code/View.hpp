/**
* @file View.hpp
* @brief Codigo de View
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <Color_Buffer.hpp>
    #include <cstdlib>
    #include "math.hpp"
    #include "Rasterizer.hpp"
    #include <vector>
    #include "Model.hpp"
	#include "Camera.hpp"

    namespace render_engine
    {

        using  std::vector;
        using argb::Rgb888;
        using argb::Color_Buffer;

        class View
        {
        private:

            typedef Rgb888                Color;
            typedef Color_Buffer< Color > Color_Buffer;
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector< int    >      Index_Buffer;
            typedef vector< Color  >      Vertex_Colors;

        private:

            static constexpr char mill_floor_file_path[] = "../../../../shared/assets/Low-Poly-Mill-floor.obj";
			static constexpr char mill_tree_file_path[] = "../../../../shared/assets/Low-Poly-Mill-tree.obj";
			static constexpr char mill_file_path[] = "../../../../shared/assets/Low-Poly-Mill-mill.obj";

            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

			// Todos los modelos a cargar
			Model floor;			
			Model floor_grass;
			Model mill_tree_root;
			Model mill_tree_leaf;
			Model mill_root;
			Model mill_root2;
			Model mill_extras;

			///Coordenadas usadas para los inputs del usuario en main.cpp
			float x_added_position = 0; 

			///Coordenadas usadas para los inputs del usuario en main.cpp
			float y_added_position = 0;

			///Coordenadas usadas para los inputs del usuario en main.cpp
			float z_added_position = 0;

			Camera main_camera;

        public:

            View(unsigned width, unsigned height);		

			// Setters
			void set_x_position(float new_x_added_position) 
			{
				x_added_position = new_x_added_position;
			}
			void set_y_position(float new_y_added_position)
			{
				y_added_position = new_y_added_position;
			}
			void set_z_position(float new_z_added_position)
			{
				z_added_position = new_z_added_position;
			}

			// Getters
			float get_x_position() const
			{
				return x_added_position;
			} 
			float get_y_position() const
			{
				return y_added_position;
			}
			float get_z_position() const
			{
				return z_added_position;
			}

			/**
			* @brief Esta funcion se encraga de reinciar los axis de inputs para 
			* no hacer movimientos mezclados como diagonales y sucedaneos
			* @param view de que escena se resetean los valores de movimiento de la camra
			*/
			void reset_inputs(View view) 
			{
				view.set_x_position(0);
				x_added_position = 0;

				view.set_y_position(0);
				y_added_position = 0;

				view.set_z_position(0);
				z_added_position = 0;
			}

			void update_camera_position() 
			{
				main_camera.move_position({ x_added_position, 0, 0 });
				main_camera.move_position({ 0, y_added_position, 0 });
				main_camera.move_position({ 0, 0, z_added_position });
			}

            void update ();
            void render ();

        };

    }

#endif
