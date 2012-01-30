#include "main.hpp"

#include <string>

#include "camera.hpp"
#include "lights.hpp"

namespace Main {
    Window *window = NULL;
    SDL_GLContext context = NULL;

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
            "Gamelike Game", //name
            {640, 480}, //size
            {0, 20}, //topleft
        };
        window = new Window(settings);
        if (window->error) {
            Debug::error << "Create Window Error: " << window->error_msg << std::endl;
            return 1;
        }
        Debug::debug << "Window Created" << std::endl;

        SDL_SetRelativeMouseMode(SDL_TRUE);
        return 0;
    }

    int gl_init() {
        context = SDL_GL_CreateContext(window->sdl_window);
        if (context == NULL) {
            Debug::error <<  "Create Context Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Context created" << std::endl;

        if (GL::init_bindings() != 0) {
            Debug::error << "Error loading OpenGL functions." << std::endl;
            return 1;
        }

        Debug::debug << "OpenGL vendor: " << GL::GetString(GL_VENDOR) << std::endl;
        Debug::debug << "OpenGL renderer: " << GL::GetString(GL_RENDERER) << std::endl;
        Debug::debug << "OpenGL version: " << GL::GetString(GL_VERSION) << std::endl;

        GL::ClearColor(0.9, 0.9, 0.9);
        GL::Enable(GL_DEPTH_TEST);
        GL::Enable(GL_CULL_FACE);
        GL::LineWidth(3.0);

        Lights::init();

        GL::MatrixMode(GL_PROJECTION);
        GL::LoadIdentity();
        window->view.camera.perspective();

        return 0;
    }
}
