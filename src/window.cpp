#include "window.hpp"

#include "lights.hpp"

Window::Window(WindowSettings settings)
        : error(false), sdl_window(NULL), view() {
    sdl_window = SDL_CreateWindow(
            settings.name.c_str(),
            settings.topleft.x,
            settings.topleft.y,
            settings.size.width,
            settings.size.height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (sdl_window == NULL) {
        error = true;
        error_msg = SDL_GetError();
    }
}

Window::~Window() {
    if (sdl_window != NULL) {
        SDL_DestroyWindow(sdl_window);
    }
}

void Window::set_world(WorldView *world) {
    view.world = world;
}

void Window::render(double interpolation) {
    GL::Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GL::MatrixMode(GL_MODELVIEW);
    GL::LoadIdentity();
    view.camera.look(interpolation);

    Lights::display(interpolation);

    GL::CullFace(GL_BACK);
    GL::FrontFace(GL_CW);
    GL::PolygonMode(GL_FRONT, GL_FILL);

    GL::Color3f(0.59, 0.29, 0);
    view.world->display();

    SDL_GL_SwapWindow(sdl_window);
}
