#include "main.hpp"

#include "world.hpp"
#include "world_view.hpp"
#include "camera.hpp"
#include "lights.hpp"

#include <cmath>

#include <SDL_thread.h>

const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;

namespace Main {
    World *world;
    WorldView *wv;
    bool running = true;
    bool sdl_initialized = false;

    void Init() {
        if (sdl_init() != 0) {
            Debug::error << "Error starting SDL." << std::endl;
            running = false;
            return;
        }
        sdl_initialized = true;

        if (gl_init() != 0) {
            Debug::error << "Error loading OpenGL." << std::endl;
            running = false;
            return;
        }

        world = new World();
        wv = new WorldView(world);

        wv->gl_init();
    }

    void Event() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            handle_event(event);
        }
    }

    void Tick() {
        Camera::tick();
    }

    void Render(double interpolation) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Camera::look(interpolation);

        Lights::display(interpolation);

        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        glPolygonMode(GL_FRONT, GL_FILL);

        glColor3f(0.59, 0.29, 0);
        wv->display();

        SDL_GL_SwapBuffers();
    }

    void Cleanup() {
        if (wv) {
            delete wv;
        }

        if (world) {
            delete world;
        }

        if (sdl_initialized) {
            SDL_Quit();
        }
    }

    unsigned int next_game_tick;
    unsigned int current_tick;

    int UpdateThread(void *unused) {
        while (Main::running) {
            if (current_tick > next_game_tick) {
                Main::Tick();
                next_game_tick += SKIP_TICKS;
            }
        }

        return 0;
    }
}

int main(int argc, char *argv[]) {
    Main::Init();

    Main::next_game_tick = SDL_GetTicks();
    Main::current_tick = Main::next_game_tick - 1;

    SDL_Thread *update_thread = SDL_CreateThread(Main::UpdateThread, NULL);

    while (Main::running) {
        Main::current_tick = SDL_GetTicks();
        Main::Event();
        float interpolation = (Main::current_tick + SKIP_TICKS - Main::next_game_tick) / (float) SKIP_TICKS;
        Main::Render(interpolation);
    }

    SDL_WaitThread(update_thread, NULL);

    Main::Cleanup();

    return 0;
}
