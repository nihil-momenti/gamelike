#include "GL_bindings.hpp"

#include "debug.hpp"

#define DECLARE_FUNCTION(func) func ## Proc func

#define GET_FUNCTION(func) \
    do { \
        func = (func ## Proc) SDL_GL_GetProcAddress( #func ); \
        if (func == NULL) { \
            result += 1; \
            Debug::error << "Unable to find function: " << #func << std::endl; \
        } \
    } while (0)


DECLARE_FUNCTION(glClear);
DECLARE_FUNCTION(glViewport);
DECLARE_FUNCTION(glMultMatrixd);
DECLARE_FUNCTION(glTranslated);
DECLARE_FUNCTION(glMatrixMode);
DECLARE_FUNCTION(glCullFace);
DECLARE_FUNCTION(glDepthFunc);
DECLARE_FUNCTION(glPolygonMode);
DECLARE_FUNCTION(glLoadIdentity);
DECLARE_FUNCTION(glBegin);
DECLARE_FUNCTION(glEnd);
DECLARE_FUNCTION(glColor3f);
DECLARE_FUNCTION(glColor4f);
DECLARE_FUNCTION(glVertex3f);
DECLARE_FUNCTION(glClearColor);

int GL_Bindings::init() {
    int result = 0;

    GET_FUNCTION(glClear);
    GET_FUNCTION(glViewport);
    GET_FUNCTION(glMultMatrixd);
    GET_FUNCTION(glTranslated);
    GET_FUNCTION(glMatrixMode);
    GET_FUNCTION(glCullFace);
    GET_FUNCTION(glDepthFunc);
    GET_FUNCTION(glPolygonMode);
    GET_FUNCTION(glLoadIdentity);
    GET_FUNCTION(glBegin);
    GET_FUNCTION(glEnd);
    GET_FUNCTION(glColor3f);
    GET_FUNCTION(glColor4f);
    GET_FUNCTION(glVertex3f);
    GET_FUNCTION(glClearColor);

    return result;
}
