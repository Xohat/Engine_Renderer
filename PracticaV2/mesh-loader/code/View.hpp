
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
			Model tree2;

            unsigned width;
            unsigned height;

			// A + alto el primer numero diferente FOV (1 ya es muy lejos, jugar con decimales hasta 21 si se juega con ello)
			Matrix44 projection = perspective(20.6f, 1, 15, float(width) / height);

        public:

            View(unsigned width, unsigned height);

            void update ();
            void render ();

        };

    }

#endif
