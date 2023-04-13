
// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// Basado en código de Ángel
// 2023.03 - 2023.04

#include <cassert>
#include <cmath>
#include "math.hpp"
#include "View.hpp"

namespace render_engine
{

    View::View(unsigned width, unsigned height)
    :
        width       (width ),
        height      (height),
        color_buffer(width, height),
        rasterizer  (color_buffer ),
		tree		(tree_file_path),
		tree2       (tree_file_path)
    {
		tree.set_position({ 0.f, 0.f, -10.f });
		//tree.set_mesh(0);
		tree.set_scale(0.001f);
		//tree2.set_mesh();
		tree2.set_scale(0.1f);
		tree2.set_position({ 0.f, 0.f, -10.f });
		//tree2.set_parent(tree);
		//tree2.set_mesh(1);
	}

    void View::update ()
    {
		tree.update();
		//tree2.update();
    }

    void View::render ()
    {
		// Se borra el framebúffer y se dibujan los triángulos:

		rasterizer.clear();

		tree.render(rasterizer, projection, width, height);
		//tree2.render(rasterizer, projection, width, height);

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		color_buffer.blit_to_window();
    }


}
