#include "main.hpp"

#include "camera.hpp"
#include "lights.hpp"

namespace Main {
    int width = 640,
        height = 480;

    int sdl_init() {
        if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
            Debug::error << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Using SDL" << std::endl;

        if (SDL_GL_LoadLibrary( NULL ) != 0) {
            Debug::error << "SDL GL Load Library Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Loaded SDL GL Library" << std::endl;

        SDL_WM_SetCaption("Gamelike Game", "Gamelike");

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

        if (SDL_SetVideoMode(640, 480, 0, SDL_OPENGL | SDL_RESIZABLE) == NULL) {
            Debug::error << "Set Video Mode Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        Debug::debug << "Video Mode Set" << std::endl;

        SDL_ShowCursor(SDL_DISABLE);
        SDL_WM_GrabInput(SDL_GRAB_ON);
        return 0;
    }

    int gl_init() {
        if (GL_Bindings::init() != 0) {
            Debug::error << "Error loading OpenGL functions." << std::endl;
            return 1;
        }

        glClearColor(0.9, 0.9, 0.9);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glLineWidth(3.0);

        Lights::init();
        Camera::init(width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        Camera::perspective();

        return 0;
    }
}
