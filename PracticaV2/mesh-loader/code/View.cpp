
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

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
		tree2.set_position({ -1.f, 0.5f, -10.f });
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

		//model.render (projection);

		tree.render(rasterizer, projection, width, height);
		tree2.render(rasterizer, projection, width, height);

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		color_buffer.blit_to_window();
    }


}
