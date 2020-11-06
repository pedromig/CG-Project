#include "cgproject.h"

GLfloat door_angle = 0;
GLfloat cat_door_angle = 0;
GLfloat handle_angle = 0;

void draw_door_handle() {
    glPushMatrix();
    {
        glTranslatef(0, 0, 0.5);
        glScalef(0.2, 0.2, 0.8);
        draw_cylinder(1, 1);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-0.2, 0, 0.9);
        glRotatef(-90, 0, 1, 0);
        glScalef(0.2, 0.2, 1);
        draw_cylinder(1, 1);
    }
    glPopMatrix();
}

void door(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
    glPushMatrix();
    {
        glTranslatef(x, y, z);
        glRotatef(angle + door_angle, 0, 1, 0);
        glTranslatef(4, 0.5, z);

        // Door Base
        glColor4f(BROWN);
        glPushMatrix();
        {
            glScalef(8, 1, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Cat Door Left
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(-2.5, 2, 0);
            glScalef(3, 3, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Cat Door Right
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(2.5, 2, 0);
            glScalef(3, 3, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Cat Door
        glColor4f(BLUE);
        glPushMatrix();
        {
            glTranslatef(0, 3.5, 0);
            glRotatef(cat_door_angle, 1.0f, 0.0f, 0.0f);
            glTranslatef(0, -1.5, 0);
            glScalef(2, 3, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Cat Door/Textures Separator
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(0, 4, 0);
            glScalef(8, 1, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Texture Section Left
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(-3.25, 6.5, 0);
            glScalef(1.5, 4, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Texture Rectangle 1
        glColor4f(RED);
        glPushMatrix();
        {
            glTranslatef(-1.5, 6.5, 0);
            glScalef(2, 4, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Texture Section Middle
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(0, 6.5, 0);
            glScalef(1, 4, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Texture Rectangle 2
        glColor4f(RED);
        glPushMatrix();
        {
            glTranslatef(1.5, 6.5, 0);
            glScalef(2, 4, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Texture Section Right
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(3.25, 6.5, 0);
            glScalef(1.5, 4, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Door Handle Section
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(0, 9.5, 0);
            glScalef(8, 2, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();

        // Handle Location
        glColor4f(GRAY);
        glPushMatrix();
        {
            glTranslatef(3, 9.5, 0);
            glScalef(0.35, 0.3, 0.5);
            glutSolidTorus(0.6, 1, 20, 30);
        }
        glPopMatrix();

        // Door Handle
        glColor4f(BLUE);
        glPushMatrix();
        {
            glTranslatef(3, 9.5, 0);
            glRotatef(handle_angle, 0, 0, 1);
            draw_door_handle();
            glScalef(1, 1, -1);
            draw_door_handle();
        }
        glPopMatrix();

        // Glass section
        for (int i = 0; i < 3; ++i) {
            glColor4f(BROWN);
            glPushMatrix();
            {
                glTranslatef(-3.1, 11.5 + 2.5 * i, 0);
                glScalef(1.8, 2, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();

            glColor4f(BROWN);
            glPushMatrix();
            {
                glTranslatef(3.1, 11.5 + 2.5 * i, 0);
                glScalef(1.8, 2, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();

            // Left Window
            glColor4f(CYAN);
            glPushMatrix();
            {
                glTranslatef(-1.2, 11.5 + 2.5 * i, 0);
                glScalef(2, 2, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();

            // Window Separator
            glColor4f(BROWN);
            glPushMatrix();
            {
                glTranslatef(0, 11.5 + 2.5 * i, 0);
                glScalef(0.4, 2, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();

            // Right Window
            glColor4f(CYAN);
            glPushMatrix();
            {
                glTranslatef(1.2, 11.5 + 2.5 * i, 0);
                glScalef(2, 2, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();

            // Top
            glColor4f(BROWN);
            glPushMatrix();
            {
                glTranslatef(0, 12.75 + 2.5 * i, 0);
                glScalef(8, 0.5, 0.3);
                glutSolidCube(1);
            }
            glPopMatrix();
        }

        // Top
        glColor4f(BROWN);
        glPushMatrix();
        {
            glTranslatef(0, 18.25, 0);
            glScalef(8, 0.5, 0.3);
            glutSolidCube(1);
        }
        glPopMatrix();
    }
    glPopMatrix();
}