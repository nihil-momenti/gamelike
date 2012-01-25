#include "main.hpp"

#include "camera.hpp"
#include "lights.hpp"

namespace Main {
    SDL_Window *window;
    SDL_GLContext context;

    int width = 640,
        height = 480;

    int sdl_init() {
        if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
            Debug::error << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "SDL initialised" << std::endl;
        Debug::debug << "Using video driver: " << SDL_GetCurrentVideoDriver() << std::endl;

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

        window = SDL_CreateWindow("Gamelike Game", 0, 0, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (window == NULL) {
            Debug::error << "Create Window Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Window Created" << std::endl;

        context = SDL_GL_CreateContext(window);
        if (context == NULL) {
            Debug::error <<  "Create Context Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Context created" << std::endl;

        SDL_SetRelativeMouseMode(SDL_TRUE);
        return 0;
    }

    int gl_init() {
        if (GL::init_bindings() != 0) {
            Debug::error << "Error loading OpenGL functions." << std::endl;
            return 1;
        }

        Debug::debug << "OpenGL version: " << GL::GetString(GL_VERSION) << std::endl;

        GL::ClearColor(0.9, 0.9, 0.9);
        GL::Enable(GL_DEPTH_TEST);
        GL::Enable(GL_CULL_FACE);
        GL::LineWidth(3.0);

        Lights::init();
        Camera::init(width, height);

        GL::MatrixMode(GL_PROJECTION);
        GL::LoadIdentity();
        Camera::perspective();

        return 0;
    }
}
