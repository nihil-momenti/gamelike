#include "window.hpp"

#include "lights.hpp"

SDL_GLContext Window::context = NULL;
int Window::context_ref_count = 0;

Window::Window(WindowSettings settings)
        : error(false), sdl_window(NULL), view(settings.size.width, settings.size.height) {
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

    Window::context_ref_count--;
    if (Window::context != NULL && Window::context_ref_count == 0) {
        SDL_GL_DeleteContext(context);
        context = NULL;
    }
}

void Window::gl_init() {
    Window::context_ref_count++;
    if (Window::context == NULL) {
        Window::context = SDL_GL_CreateContext(sdl_window);
    }
    if (Window::context == NULL || GL::init_bindings() != 0) {
        error = true;
        error_msg = SDL_GetError();
        return;
    }

    GL::ClearColor(0.9, 0.9, 0.9);
    GL::Enable(GL_DEPTH_TEST);
    GL::Enable(GL_CULL_FACE);
    GL::LineWidth(3.0);

    Lights::init();

    GL::MatrixMode(GL_PROJECTION);
    GL::LoadIdentity();

    view.camera.gl_init();
    view.camera.perspective();
}

void Window::set_world(WorldView *world) {
    view.world = world;
    SDL_GL_MakeCurrent(sdl_window, Window::context);
    world->gl_init();
}

void Window::render(double interpolation) {
    SDL_GL_MakeCurrent(sdl_window, Window::context);

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
