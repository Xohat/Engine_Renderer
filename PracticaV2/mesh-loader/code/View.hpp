
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

            static constexpr char tree_file_path[] = "../../../../shared/assets/Tree.fbx";
			static constexpr char mesh_file_path_2[] = "../../../../shared/assets/Tree2.fbx";

            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

			Model tree;
			Model tree_leaf;

            unsigned width;
            unsigned height;

			float x_added_position = 0;
			float y_added_position = 0;
			float z_added_position = 0;

			Camera main_camera;

        public:

            View(unsigned width, unsigned height);		

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
				main_camera.set_position({
					main_camera.get_position().x + x_added_position,
					main_camera.get_position().y + y_added_position,
					main_camera.get_position().z + z_added_position });
			}

            void update ();
            void render ();

        };

    }

#endif
