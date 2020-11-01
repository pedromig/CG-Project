#include "pch.h"

// World Settings
#define CANVAS_WIDTH 1800
#define CANVAS_HEIGHT 1200

// Utility
#define ESC_KEY 27

// Camera Settings
GLfloat camera_radius = 15.0f;
GLfloat camera_angle = M_PI_4;
GLdouble camera[] = {camera_radius * cos(camera_angle),
                    10.0f,
                    camera_radius *sin(camera_angle)};

#define WORLD_XYZ_NEAR 0.1f
#define WORLD_XYZ_FAR 100.0f

#define CAMERA_SPEED 0.1f
#define ZOOM_SPEED 0.1f
#define ANGLE_SPEED 0.1f

#define CAMERA_FOV_Y (GLfloat)95
#define CAMERA_FOV_X (GLfloat)(CANVAS_WIDTH / CANVAS_HEIGHT)

#define TO_RADIANS(ANGLE) M_PI *ANGLE / 180.0f

// Door Settings
GLfloat door_angle = 0;
GLfloat cat_door_angle = 0;
GLfloat handle_angle = 0;

#define ROTATE_SPEED 1.0f

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
            door_angle += ROTATE_SPEED;
            break;
        case 'E':
            door_angle -= ROTATE_SPEED;
            break;
        case 'F':
            cat_door_angle += ROTATE_SPEED;
            break;
        case 'D':
            cat_door_angle -= ROTATE_SPEED;
            break;
        case 'A':
            handle_angle += ROTATE_SPEED;
            break;
        case 'S':
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

void debug_axis() {
    // X Axis
    glColor4f(RED);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(WORLD_XYZ_FAR, 0.0f, 0.0f);
    }
    glEnd();

    // Y Axis
    glColor4f(GREEN);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, WORLD_XYZ_FAR, 0.0f);
    }
    glEnd();

    // Z Axis
    glColor4f(BLUE);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, WORLD_XYZ_FAR);
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

void draw_cylinder(GLfloat radius) {
    GLfloat x, y, z0, z1;
    int s = 10;
    for (int i = 0; i < s; i++) {
        z0 = (GLfloat) (i / s);
        z1 = ((GLfloat) ((i + 1) / s));
        glBegin(GL_QUAD_STRIP);
        {
            for (int j = 0; j <= 360; ++j) {
                x = radius * cos(TO_RADIANS(j));
                y = radius * sin(TO_RADIANS(j));
                glVertex3f(x, y, z0);
                glVertex3f(x, y, z1);
            }
        }
        glEnd();
    }
    draw_circle(x, y, 0, radius);
    draw_circle(x, y, z1, radius);
}

void draw_door_handle() {    
    glPushMatrix();
    {
        glTranslatef(0, 0, 0);
        glScalef(0.2, 0.2, 0.8);
        draw_cylinder(1);
    }
    glPopMatrix();

    glPushMatrix();
    {   
        glTranslatef(0.2, 0, 0.8);
        glRotatef(-90 , 0, 1, 0);
        glScalef(0.2, 0.2, 1);
        draw_cylinder(1);
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
            glutSolidTorus(0.5, 1, 20, 30);
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
