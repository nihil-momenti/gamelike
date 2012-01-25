#include "lights.hpp"

#include "GL_bindings.hpp"

namespace Lights {
    void init() {
        GLfloat ambient[4] = {0.0, 0.0, 0.0, 1.0};
        GLfloat diffuse[4] = {1.0, 1.0, 1.0, 1.0};

        GL::Lightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
        GL::Lightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
        GL::Lightfv(GL_LIGHT0, GL_SPECULAR, diffuse);

        GLfloat emission[4] = {0.0, 0.0, 0.0, 1.0};
        GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};

        GL::Materialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
        GL::Materialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        GL::Materiali(GL_FRONT_AND_BACK, GL_SHININESS, 60);

        GL::ColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        GL::LightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        GL::Enable(GL_COLOR_MATERIAL);
        GL::Enable(GL_LIGHTING);
        GL::Enable(GL_LIGHT0);
    }

    void display(double interpolation) {
        GLfloat position[4] = {1.0, 1.0, 1.0, 0.0};
        GL::Lightfv(GL_LIGHT0, GL_POSITION, position);
    }
}
