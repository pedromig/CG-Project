/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#include "cgproject.h"

GLfloat door_angle = 0;
GLfloat cat_door_angle = 0;
GLfloat handle_angle = 0;
GLfloat latch_dx = 0;

void draw_door_handle() {
    glPushMatrix();
    {
        glTranslatef(0, 0, 0.3);
        glScalef(0.2, 0.2, 0.8);
        draw_cylinder(1, 1);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(-0.30, 0, 0.7);
        glRotatef(-90, 0, 1, 0);
        glScalef(0.2, 0.2, 1);
        draw_cylinder(1, 1);
    }
    glPopMatrix();
}

void door(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {

    glPushMatrix();
    {

        glBlendFunc(GL_ONE, GL_ZERO);
        glTranslatef(x, y, z);
        glRotatef(angle + door_angle, 0, 1, 0);
        glTranslatef(4, 0.5, z);

        // Door Base
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        select_material(DEFAULT);
        glPushMatrix();
        {
            glScalef(8, 1, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Cat Door Left
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(-2.5, 2, 0);
            glScalef(3, 3, 0.3);

            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Cat Door Right
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(2.5, 2, 0);
            glScalef(3, 3, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        select_material(PLASTIC);
        // Cat Door
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glPushMatrix();
        {
            GLfloat shift_rotation_center = cat_door_angle > 0 ? 0.15f : -0.15f;

            glTranslatef(0, 3.5, -shift_rotation_center);
            glRotatef(cat_door_angle, 1.0f, 0.0f, 0.0f);
            glTranslatef(0, -1.5, shift_rotation_center);
            glScalef(2, 3, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Cat Door texture separator
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(0, 4, 0);
            glScalef(8, 1, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Texture Section Left
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(-3.25, 6.5, 0);
            glScalef(1.5, 4, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Texture Rectangle 1
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(-1.5, 6.5, 0);
            glScalef(2, 4, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Texture Section Middle
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(0, 6.5, 0);
            glScalef(1, 4, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Texture Rectangle 2
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(1.5, 6.5, 0);
            glScalef(2, 4, 0.3);

            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Texture Section Right
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(3.25, 6.5, 0);
            glScalef(1.5, 4, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Door Handle Section
        select_material(DEFAULT);
        glPushMatrix();
        {
            glTranslatef(0, 9.5, 0);
            glScalef(8, 2, 0.3);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Handle Location
        glDisable(GL_TEXTURE_2D);
        select_material(CHROME);
        glPushMatrix();
        {
            glTranslatef(3, 9.5, 0);
            glScalef(0.35, 0.3, 0.5);
            glutSolidTorus(0.6, 1, 20, 30);
        }
        glPopMatrix();

        // Door Latch
        select_material(CHROME);
        glPushMatrix();
        {
            glTranslatef(4 - latch_dx, 9.5, 0);
            glScalef(0.3, 0.3, 0.05);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Door Handle
        select_material(CHROME);
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
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        for (int i = 0; i < 3; ++i) {

            select_material(DEFAULT);
            glPushMatrix();
            {
                glTranslatef(-3.1, 11.5 + 2.5 * i, 0);
                glScalef(1.8, 2, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();

            select_material(DEFAULT);
            glPushMatrix();
            {
                glTranslatef(3.1, 11.5 + 2.5 * i, 0);
                glScalef(1.8, 2, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();

            // Window Separator
            select_material(DEFAULT);
            glPushMatrix();
            {
                glTranslatef(0, 11.5 + 2.5 * i, 0);
                glScalef(0.4, 2, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();

            // Top
            select_material(DEFAULT);
            glPushMatrix();
            {
                glTranslatef(0, 12.75 + 2.5 * i, 0);
                glScalef(8, 0.5, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();
        }

        // Top
        glPushMatrix();
        {
            glTranslatef(0, 18.25, 0);
            glScalef(8, 0.5, 0.3);
            select_material(DEFAULT);
            draw_cube(1, use_grid);
        }
        glPopMatrix();

        // Glass Windows
      
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
        glColor4f(0.10754, 0.10754, 0.2054, 0.3);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        for (int i = 0; i < 3; ++i) {
            // Left Window
            glPushMatrix();
            {
                glTranslatef(-1.2, 11.5 + 2.5 * i, 0);
                glScalef(2, 2, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();

            // Right Window
            glPushMatrix();
            {
                glTranslatef(1.2, 11.5 + 2.5 * i, 0);
                glScalef(2, 2, 0.3);
                draw_cube(1, use_grid);
            }
            glPopMatrix();
        }
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}