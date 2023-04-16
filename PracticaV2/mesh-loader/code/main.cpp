
/**
* @file main.cpp
* @brief Archivo main
* @author Arturo Vilar Carretero
*/

// Copyright (c) 2023 Arturo / Xohat
// arturovilarc@gmail.com / xohatlatte@gmail.com
// 2023.03 - 2023.04

#include "View.hpp"
#include <SFML/Window.hpp>

#include "Model.hpp"

using namespace sf;
using namespace render_engine;

int main ()
{
    // Create the window and the view that will be shown within the window:

    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    Window window(VideoMode(window_width, window_height), "Mesh Loader", Style::Titlebar | Style::Close);
    View   view  (window_width, window_height);

    window.setVerticalSyncEnabled (true);

    // Run the main loop:

    bool exit = false;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
			switch (event.type) 
			{
				case Event::Closed:
						exit = true;
						break;

				// Se encarga de los inputs para el movimeinto de la camara
				case Event::KeyPressed:
					switch (event.key.code)
					{
						// Axis inputs
						case Keyboard::Key::W:
							view.set_y_position(0.5f);
							view.update_camera_position();
							break;

						case Keyboard::Key::A:
							view.set_x_position(0.5f);
							view.update_camera_position();
							break;

						case Keyboard::Key::S:
							view.set_y_position(-0.5f);
							view.update_camera_position();
							break;

						case Keyboard::Key::D:
							view.set_x_position(-0.5f);
							view.update_camera_position();
							break;

						// Zoom inputs
						case Keyboard::Key::Up:
							view.set_z_position(-0.5f);
							view.update_camera_position();
							break;

						case Keyboard::Key::Down:
							view.set_z_position(0.5f);
							view.update_camera_position();
							break;
					}
			}
        }

        view.update ();

        view.render ();

		view.reset_inputs(view);

        window.display ();
    }
    while (not exit);

    return 0;
}
