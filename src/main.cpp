//#include <glew.h>
#include <SDL.h>
#include "GL_bindings.hpp"

#include "debug.hpp"

#include "world.hpp"
#include "world_view.hpp"
#include "player.hpp"

#include <cmath>

namespace Main {
    WorldView wv;
    Player player;
    bool running = true;

    void sdl_init() {
        if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
            Debug::error << "SDL Initialisation Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        Debug::debug << "Using SDL" << std::endl;

        if (SDL_GL_LoadLibrary( NULL ) != 0) {
            Debug::error << "SDL GL Load Library Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);
        }
        Debug::debug << "Video Mode Set" << std::endl;
    }

    void Init() {
        sdl_init();
        if (GL_Bindings::init() != 0) {
            Debug::error << "Error loading OpenGL functions." << std::endl;
        }
        Debug::debug << "Loaded OpenGL functions." << std::endl;
        World world = World::gen_random();
        wv = WorldView(world);
        glClearColor(0.9, 0.9, 0.9);
    }

    void Event() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }

    void Tick() {
        player.tick();
    }

    void Render() {
        glViewport(0, 0, 640, 480);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        double aspect = 1.0,
               fov = 50.0,
               near = 0.1,
               far = 100.0;
        double f = cos(fov / 2) / sin(fov / 2);
        GLdouble M[16] = {
            f / aspect, 0.0,    0.0,                            0.0,
            0.0,        f,      0.0,                            0.0,
            0.0,        0.0,    (far + near) / (near - far),    (2 * far * near) / (near - far),
            0.0,        0.0,    -1.0,                           0.0
        };

        glMultMatrixd(M);
        //gluPerspective(50.0, 1.0, 0.1, 1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        player.look();

        glPolygonMode(GL_FRONT, GL_FILL);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);
        glColor4f(0.44, 0.31, 0.21, 1.0);

        glBegin(GL_QUADS);
            glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
            glColor3f(1, 1, 0); glVertex3f(1, 0, 0);
            glColor3f(1, 0, 1); glVertex3f(1, 1, 0);
            glColor3f(1, 1, 1); glVertex3f(0, 1, 0);
        glEnd();

        //wv.display();

        SDL_GL_SwapBuffers();
    }

    void Cleanup() {
        SDL_Quit();
    }
}

int main(int argc, char *argv[]) {
    Main::Init();

    while (Main::running) {
        Main::Event();
        Main::Tick();
        Main::Render();
    }

    Main::Cleanup();

    return 0;
}
