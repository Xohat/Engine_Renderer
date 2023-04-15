
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2021.12 - 2021.04

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

	float test_x_pos = 0;

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

				case Event::KeyPressed:
					switch (event.key.code)
					{
						case Keyboard::Key::A:
							test_x_pos += 10.f;
							view.set_x_position(test_x_pos);
							break;
					}
			}
        }

        view.update ();

        view.render ();

        window.display ();
    }
    while (not exit);

    return 0;
}
