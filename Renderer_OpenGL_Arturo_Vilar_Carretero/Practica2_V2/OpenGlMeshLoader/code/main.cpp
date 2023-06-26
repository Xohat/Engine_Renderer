
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include <cassert>
#include <glad/glad.h>
#include <SFML/Window.hpp>
#include "View.hpp"

using namespace sf;
using namespace example;

int main ()
{
    // Se crea la ventana de SFML, que es donde se creará el contexto de OpenGL:

    Window window(VideoMode(800, 600), "Mesh Loader", Style::Default, ContextSettings(24, 0, 0, 3, 3, ContextSettings::Core));

    // Una vez se ha creado el contexto de OpenGL ya se puede inicializar GLAD:

    GLenum glad_initialization =  gladLoadGL ();

    assert(glad_initialization != 0);

    // GLAD se inicializa antes de crear view porque view ya usa extensiones de OpenGL:

    View view(800, 600);

    window.setVerticalSyncEnabled (true);

    bool running = true;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
			glm::vec3 camera_pos = view.get_camera()->get_position();

            switch (event.type)
            {
                // Si se clica la X para cerrar la window
                case Event::Closed:
                {
                    running = false;
                    break;
                }

                // Si la window se pone fullscreen
                case Event::Resized:
                {
                    Vector2u window_size = window.getSize ();

                    view.resize (window_size.x, window_size.y);

                    break;
                }
                
                // Revisa si una tecla ha sido presionada
                case Event::KeyPressed:
                {
                    // Mueve la cámara hacia adelante en la z
                    if (event.key.code == sf::Keyboard::LShift)
                    {
                        camera_pos.z += 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }
                    // Mueve la cámara hacia stras en la z
                    if (event.key.code == sf::Keyboard::LControl)
                    {
                        camera_pos.z -= 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }
                    // Mueve la cámara hacia arriba en la y
                    if (event.key.code == sf::Keyboard::W) 
                    {
                        camera_pos.y += 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }
                    // Mueve la cámara hacia abajo en la y
                    if (event.key.code == sf::Keyboard::S)
                    {
                        camera_pos.y -= 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }
                    // Mueve la cámara hacia la izquierda en la x
                    if (event.key.code == sf::Keyboard::A)
                    {
                        camera_pos.x -= 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }
                    // Mueve la cámara hacia la derecha en la x
                    if (event.key.code == sf::Keyboard::D)
                    {
                        camera_pos.x += 0.25f;
                        view.get_camera()->set_position({ camera_pos.x, camera_pos.y, camera_pos.z });
                    }

                    break;
                }
            }
        }

        // Activa el método update
        view.update ();
        // Activa el método render
        view.render ();

        window.display ();
    }
    while (running);

    return EXIT_SUCCESS;
}
