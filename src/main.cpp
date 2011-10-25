#include "main.hpp"

#include "world.hpp"
#include "world_view.hpp"
#include "camera.hpp"
#include "lights.hpp"

#include <cmath>

namespace Main {
    WorldView wv;
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

        World world;
        wv = WorldView(world);
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
        wv.display();

        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);
        glPolygonMode(GL_BACK, GL_LINE);

        glColor3f(0.0, 0.0, 0);
        wv.display();

        SDL_GL_SwapBuffers();
    }

    void Cleanup() {
        if (sdl_initialized) {
            SDL_Quit();
        }
    }
}

const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

int main(int argc, char *argv[]) {
    Main::Init();

    unsigned int next_game_tick = SDL_GetTicks();
    int loops;
    float interpolation;

    while (Main::running) {
        loops = 0;
        while (SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            Main::Event();
            Main::Tick();
            next_game_tick += SKIP_TICKS;
            loops++;
        }

        interpolation = (SDL_GetTicks() + SKIP_TICKS - next_game_tick) / (float) SKIP_TICKS;
        Main::Render(interpolation);
    }

    Main::Cleanup();

    return 0;
}
