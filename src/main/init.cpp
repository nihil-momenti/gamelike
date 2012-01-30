#include "main.hpp"

#include <string>

#include "camera.hpp"
#include "lights.hpp"

namespace Main {
    Window *window = NULL;
    Window *window2 = NULL;

    int width = 640,
        height = 480;

    int sdl_init() {
        if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
            Debug::error << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "SDL initialised" << std::endl;
        Debug::debug << "Using video driver: " << SDL_GetCurrentVideoDriver() << std::endl;

        sdl_initialized = true;

        if (SDL_GL_LoadLibrary( NULL ) != 0) {
            Debug::error << "SDL GL Load Library Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Loaded SDL GL Library" << std::endl;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        WindowSettings settings = {
            "Gamelike Game 1", //name
            {640, 480}, //size
            {0, 20}, //topleft
        };
        window = new Window(settings);
        if (window->error) {
            Debug::error << "Create Window 1 Error: " << window->error_msg << std::endl;
            return 1;
        }
        WindowSettings settings2 = {
            "Gamelike Game 2", //name
            {640, 480}, //size
            {650, 20}, //topleft
        };
        window2 = new Window(settings2);
        if (window2->error) {
            Debug::error << "Create Window 2 Error: " << window2->error_msg << std::endl;
            return 1;
        }
        Debug::debug << "Windows Created" << std::endl;

        SDL_SetRelativeMouseMode(SDL_TRUE);
        return 0;
    }

    int gl_init() {
        window->gl_init();
        if (window->error) {
            Debug::error <<  "Create Context Window 1 Error: " << window->error_msg << std::endl;
        }

        window2->gl_init();
        if (window2->error) {
            Debug::error <<  "Create Context Window 2 Error: " << window2->error_msg << std::endl;
        }
        Debug::debug << "Window Contexts created" << std::endl;

        // Move window 2 slightly right.
        window2->view.camera.move(RIGHT);
        for (int i = 0; i < 10; i++) {
            window2->view.camera.tick();
        }
        window2->view.camera.stop(RIGHT);

        Debug::debug << "OpenGL vendor: " << GL::GetString(GL_VENDOR) << std::endl;
        Debug::debug << "OpenGL renderer: " << GL::GetString(GL_RENDERER) << std::endl;
        Debug::debug << "OpenGL version: " << GL::GetString(GL_VERSION) << std::endl;

        return 0;
    }
}
