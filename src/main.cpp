//#include <glew.h>
#include <SDL.h>
#include "GL_bindings.hpp"

#include "debug.hpp"

#include "world.hpp"
#include "world_view.hpp"
#include "camera.hpp"

#include <cmath>

namespace Main {
    WorldView wv;
    bool running = true;
    Vector3 colour(0.0, 0.0, 0.0);

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
        //Camera::tick();
        static Vector3 delta(0.01, 0.01, 0.01);
        colour += delta;
        if (delta.dx > 0 && colour.dx >= 1.0) {
            delta = -delta;
        } else if (delta.dx < 0 && colour.dx <= 0.0) {
            delta = -delta;
        }
    }

    void Render() {
        glViewport(0, 0, 640, 480);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(colour.dx, colour.dy, colour.dz);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        Camera::perspective();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Camera::look();

//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);
//        glFrontFace(GL_CCW);
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glColor4f(0.44, 0.31, 0.21, 1.0);

        for (int x = -100; x < 100; x = x+10) {
            for (int y = -100; y < 100; y = y+10) {
                for (int z = -100; z < 100; z = z+10) {
                    glBegin(GL_TRIANGLES);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);
                        glColor3f(1, 1, 0); glVertex3f(x+1, y+1, z-1);
                        glColor3f(1, 0, 1); glVertex3f(x+1, y-1, z-1);

                        glColor3f(1, 0, 1); glVertex3f(x+1, y-1, z-1);
                        glColor3f(1, 1, 1); glVertex3f(x+1, y-1, z+1);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);

                        glColor3f(1, 0, 0); glVertex3f(x-1, y+1, z+1);
                        glColor3f(1, 1, 0); glVertex3f(x-1, y-1, z+1);
                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);

                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);
                        glColor3f(1, 1, 1); glVertex3f(x-1, y+1, z-1);
                        glColor3f(1, 0, 0); glVertex3f(x-1, y+1, z+1);

                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);
                        glColor3f(1, 1, 0); glVertex3f(x+1, y-1, z+1);
                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z+1);

                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z+1);
                        glColor3f(1, 1, 1); glVertex3f(x-1, y+1, z+1);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);

                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z-1);
                        glColor3f(1, 1, 0); glVertex3f(x-1, y+1, z-1);
                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);

                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);
                        glColor3f(1, 1, 1); glVertex3f(x+1, y-1, z-1);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z-1);

                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);
                        glColor3f(1, 1, 0); glVertex3f(x-1, y+1, z+1);
                        glColor3f(1, 0, 1); glVertex3f(x-1, y+1, z-1);

                        glColor3f(1, 0, 1); glVertex3f(x-1, y+1, z-1);
                        glColor3f(1, 1, 1); glVertex3f(x+1, y+1, z-1);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y+1, z+1);

                        glColor3f(1, 0, 0); glVertex3f(x+1, y-1, z+1);
                        glColor3f(1, 1, 0); glVertex3f(x+1, y-1, z-1);
                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);

                        glColor3f(1, 0, 1); glVertex3f(x-1, y-1, z-1);
                        glColor3f(1, 1, 1); glVertex3f(x-1, y-1, z+1);
                        glColor3f(1, 0, 0); glVertex3f(x+1, y-1, z+1);
                    glEnd();
                }
            }
        }

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
