/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#include "cgproject.h"

// Texture Array
GLuint texture[6];


void draw_callback(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CAMERA_FOV_Y, CAMERA_FOV_X, WORLD_XYZ_NEAR, WORLD_XYZ_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera[0], camera[1], camera[2], 0, 10, 0, 0, 1, 0);

    debug_axis();
    update_light(GL_LIGHT0);
    update_light(GL_LIGHT1);
    door(0.0, 0.0, 0.0, 0.0);
    
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    // Window Settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("CG-Project - Door");

    glClearColor(BLACK);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // Ambient Lighting Setup
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (const GLfloat[4]){0.2f, 0.2f, 0.2f, 0.2f});
    update_light(GL_LIGHT0);
    update_light(GL_LIGHT1);

    // Texture Loading
    load_texture(&texture[0], "../resources/cat_door.bmp");
    load_texture(&texture[1], "../resources/wood.bmp");
    load_texture(&texture[2], "../resources/glass.bmp");

    // Window Callbacks
    glutDisplayFunc(draw_callback);
    glutSpecialFunc(non_ascii_keyboard_callback);
    glutKeyboardFunc(ascii_keyboard_callback);

    glutMainLoop();

    return EXIT_SUCCESS;
}
