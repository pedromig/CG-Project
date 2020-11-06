#include "cgproject.h"

// Camera Settings
GLfloat camera_radius = 15.0f;
GLfloat camera_angle = M_PI_4;
GLdouble camera[] = {camera_radius * cos(camera_angle),
                     10.0f,
                     camera_radius *sin(camera_angle)};


#define CAMERA_FOV_Y (GLfloat)95
#define CAMERA_FOV_X (GLfloat)(CANVAS_WIDTH / CANVAS_HEIGHT)


void update_camera() {
    if (camera[1] > WORLD_XYZ_FAR) camera[1] = WORLD_XYZ_FAR;
    if (camera[1] < -WORLD_XYZ_FAR) camera[1] = -WORLD_XYZ_FAR;

    camera[0] = camera_radius * cos(camera_angle);
    camera[2] = camera_radius * sin(camera_angle);
}

void ascii_keyboard_callback(unsigned char key, int x, int y) {

    switch (toupper(key)) {
        case 'Z':
            if (camera_radius > WORLD_XYZ_NEAR) {
                camera_radius -= ZOOM_SPEED;
                update_camera();
            }
            break;
        case 'R':
            if (door_angle < 90)
                door_angle += ROTATE_SPEED;
            break;
        case 'E':
            if (door_angle > 0)
                door_angle -= ROTATE_SPEED;
            break;
        case 'F':
            if (cat_door_angle < 90)
                cat_door_angle += ROTATE_SPEED;
            break;
        case 'D':
            if (cat_door_angle > -90)
                cat_door_angle -= ROTATE_SPEED;
            break;
        case 'A':
            if (handle_angle < 45)
                handle_angle += ROTATE_SPEED;
            break;
        case 'S':
            if (handle_angle > 0)
                handle_angle -= ROTATE_SPEED;
            break;
        case 'X':
            camera_radius += ZOOM_SPEED;
            update_camera();
            break;
        case ESC_KEY:
            exit(EXIT_SUCCESS);
            break;
    }
    glutPostRedisplay();
}

void non_ascii_keyboard_callback(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            camera[1] += CAMERA_SPEED;
            break;
        case GLUT_KEY_DOWN:
            camera[1] -= CAMERA_SPEED;
            break;
        case GLUT_KEY_LEFT:
            camera_angle += ANGLE_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            camera_angle -= ANGLE_SPEED;
            break;
    }
    update_camera();
    glutPostRedisplay();
}

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
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // Window Callbacks
    glutDisplayFunc(draw_callback);
    glutSpecialFunc(non_ascii_keyboard_callback);
    glutKeyboardFunc(ascii_keyboard_callback);

    glutMainLoop();

    return EXIT_SUCCESS;
}
