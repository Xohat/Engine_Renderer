
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
        width       (width ),
        height      (height),
        color_buffer(width, height),
        rasterizer  (color_buffer ),
		tree		(tree_file_path),
		tree2       (tree_file_path),
		main_camera (20.6f, 1, 15, width, height)
    {
		tree.set_position({ 0.f, 0.f, -10.f });
		tree.set_scale(0.3f);

		tree2.set_scale(0.45f);
		tree2.set_position({ 0.f, 0.f, -10.f });
		tree2.set_parent(tree);

		main_camera.set_position({ 0.f, -2.5f, -2.5f });
    }

    void View::update ()
    {
		tree.update();
		tree2.update();
    }

    void View::render ()
    {
		// Se borra el framebúffer y se dibujan los triángulos:

		rasterizer.clear();

		tree.render(rasterizer, main_camera);
		tree2.render(rasterizer, main_camera);

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		color_buffer.blit_to_window();
    }


}
