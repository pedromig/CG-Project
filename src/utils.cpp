#include "cgproject.h"

void debug_axis() {
    // X Axis
    glColor4f(RED);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);
    }
    glEnd();

    // Y Axis
    glColor4f(GREEN);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);
    }
    glEnd();

    // Z Axis
    glColor4f(BLUE);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    }
    glEnd();
}

void draw_circle(GLfloat x, GLfloat y, GLfloat z, int radius) {
    glBegin(GL_POLYGON);
    {
        for (int angle = 0; angle <= 360; ++angle) {
            x = radius * cos(TO_RADIANS(angle));
            y = radius * sin(TO_RADIANS(angle));
            glVertex3f(x, y, z);
        }
    }
    glEnd();
}

void draw_cylinder(GLfloat radius, GLfloat height) {
    GLfloat x, y, z0, z1;
    glBegin(GL_QUAD_STRIP);
    {
        for (int j = 0; j <= 360; ++j) {
            x = radius * cos(TO_RADIANS(j));
            y = radius * sin(TO_RADIANS(j));
            glVertex3f(x, y, -height/2);
            glVertex3f(x, y, height/2);
        }
    }
    glEnd();
    draw_circle(x, y, -height / 2, radius);
    draw_circle(x, y, -height / 2, radius);
}
