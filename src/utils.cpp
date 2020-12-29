/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#include "cgproject.h"

// Camera Settings
GLfloat camera_radius = 25.0f;
GLfloat camera_angle = M_PI_4;
GLdouble camera[] = {camera_radius * cos(camera_angle),
                     10.0f,
                     camera_radius *sin(camera_angle)};

//  Light Properties

// Light Bulb - GL_LIGHT0
bool light_bulb_on = false;
GLfloat light_bulb_intensity = 1;
GLfloat light_bulb_r = 0.5f, light_bulb_g = 0.5f, light_bulb_b = 0.5f;

GLfloat light_bulb_position[4] = {4.0f, 7.0f, 10.0f, 1.0f};
GLfloat light_bulb_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat light_bulb_specular[4] = {light_bulb_r, light_bulb_g, light_bulb_b, 1.0f};
GLfloat light_bulb_difuse[4] = {light_bulb_r, light_bulb_g, light_bulb_b, 1.0f};

// Spot Light - GL_LIGHT1
bool spotlight_on = false;
GLfloat spotlight_intensity = 1;
GLfloat spotlight_r = 0.5, spotlight_g = 0.5, spotlight_b = 0.5;

GLfloat spotlight_position[4] = {4.0f, 7.0f, -10.0f, 1.0f};
GLfloat spotlight_direction[4] = {0.0f, 0.0f, 1.0f, 0.0f};

GLfloat spotlight_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat spotlight_difuse[4] = {spotlight_r, spotlight_g, spotlight_b, 1.0f};
GLfloat spotlight_specular[4] = {spotlight_r, spotlight_g, spotlight_b, 1.0f};

GLfloat spot_cutoff = 15;
GLfloat spot_exponent = 2;

GLfloat spotlight_kc = 0.2;
GLfloat spotlight_kl = 0.05f;
GLfloat spotlight_kq = 0.0f;

GLfloat ks = 0.25;
bool use_grid = true;

// Cube general properties
static GLint faces[6][4] = {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3},
};

static GLfloat normals[6][3] = {
    {-1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -1.0f},
};

static GLfloat cube_grid_rotate[6][4] = {
    {90.0f, -1.0f, 0.0f, 0.0f},
    {90.0f, 0.0f, 1.0f, 0.0f},
    {90.0f, 1.0f, 0.0f, 0.0f},
    {90.0f, 0.0f, -1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {180.0f, 0.0f, 1.0f, 0.0f},
};

static GLfloat texture_coordinates[4][2] = {
    {0.0f, 0.0f},
    {1.0f, 0.0f},
    {1.0f, 1.0f},
    {0.0f, 1.0f},
};

void debug_axis() {
    glDisable(GL_LIGHTING);
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
    glEnable(GL_LIGHTING);
}

void draw_circle(GLfloat x, GLfloat y, GLfloat z, int radius) {
    glBegin(GL_POLYGON);
    {
        for (GLfloat angle = 0; angle <= 2 * M_PI; angle += 0.1) {
            GLfloat c = cos(angle);
            GLfloat s = sin(angle);

            glTexCoord2d(c * 0.5 + 0.5, s * 0.5 + 0.5);

            GLfloat _x = x + radius * c;
            GLfloat _y = y + radius * s;
            glVertex3f(_x, _y, z);
        }
    }
    glEnd();
}

void draw_cylinder(GLfloat radius, GLfloat height) {
    GLfloat x, y, z0, z1;
    glBegin(GL_QUAD_STRIP);
    {
        for (GLfloat j = 0; j <= 2 * M_PI + 0.1; j += 0.1) {
            GLfloat c = cos(j);
            GLfloat s = sin(j);

            glNormal3f(c, s, 1.0f);
            x = radius * c;
            y = radius * s;

            glTexCoord2d(j / (2 * M_PI), 0.0);
            glVertex3f(x, y, -height / 2);

            glTexCoord2d(j / (2 * M_PI), 1.0);
            glVertex3f(x, y, height / 2);
        }
    }
    glEnd();

    glNormal3f(0.0f, 0.0f, 1.0f);
    draw_circle(0, 0, height / 2, radius);
    glNormal3f(0.0f, 0.0f, -1.0f);
    draw_circle(0, 0, -height / 2, radius);
}

void square_grid(int size) {
    int s = size / (GLfloat)2;
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {

                glTexCoord2f((GLfloat)j / size, (GLfloat)i / size);
                glVertex3d((GLfloat)j / s, (GLfloat)i / s, 0);

                glTexCoord2f((GLfloat)(j + 1) / size, (GLfloat)i / size);
                glVertex3d((GLfloat)(j + 1) / s, (GLfloat)i / s, 0);

                glTexCoord2f((GLfloat)(j + 1) / size, (GLfloat)(i + 1) / size);
                glVertex3d((GLfloat)(j + 1) / s, (GLfloat)(i + 1) / s, 0);

                glTexCoord2f((GLfloat)j / size, (GLfloat)(i + 1) / size);
                glVertex3d((GLfloat)j / s, (GLfloat)(i + 1) / s, 0);
            }
        }
    }
    glEnd();
}

void draw_cube(GLfloat side, bool use_square_grid) {
    GLfloat cube[8][3];

    // vertex x coordinates
    cube[0][0] = cube[1][0] = cube[2][0] = cube[3][0] = -side / 2;
    cube[4][0] = cube[5][0] = cube[6][0] = cube[7][0] = side / 2;

    // vertex y coordinates
    cube[0][1] = cube[1][1] = cube[4][1] = cube[5][1] = -side / 2;
    cube[2][1] = cube[3][1] = cube[6][1] = cube[7][1] = side / 2;

    // vertex z coordinates
    cube[0][2] = cube[3][2] = cube[4][2] = cube[7][2] = -side / 2;
    cube[1][2] = cube[2][2] = cube[5][2] = cube[6][2] = side / 2;

    for (int i = 0; i < 6; ++i) {
        if (use_square_grid) {
            glPushMatrix();
            {
                glRotatef(cube_grid_rotate[i][0], cube_grid_rotate[i][1], cube_grid_rotate[i][2], cube_grid_rotate[i][3]);
                glTranslatef(-0.5f, -0.5f, 0.5f);
                glScalef(0.5f, 0.5f, 1.0f);
                square_grid(64);
            }
            glPopMatrix();
        } else {
            glBegin(GL_QUADS);
            {
                glNormal3fv((GLfloat *)normals[i]);
                for (int j = 0; j < 4; ++j) {
                    glTexCoord2fv((GLfloat *)texture_coordinates[j]);
                    glVertex3fv((GLfloat *)cube[faces[i][j]]);
                }
            }
            glEnd();
        }
    }
}

void load_texture(GLuint *texture_id, const char *texture_file) {
    RgbImage img;

    glGenTextures(1, texture_id);
    glBindTexture(GL_TEXTURE_2D, *texture_id);
    img.LoadBmpFile(texture_file);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 img.GetNumCols(),
                 img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
}

void select_material(material_t index) {
    switch (index) {
        case CHROME:
            glMaterialfv(GL_FRONT, GL_AMBIENT, (const GLfloat[3]){0.05f, 0.05f, 0.05f});
            glMaterialfv(GL_FRONT, GL_DIFFUSE, (const GLfloat[3]){0.4f, 0.4f, 0.4f});
            glMaterialfv(GL_FRONT, GL_SPECULAR, (const GLfloat[3]){0.774597f, 0.774597f, 0.774597f});
            glMaterialf(GL_FRONT, GL_SHININESS, ks * 128);
            break;
        case PLASTIC:
            glMaterialfv(GL_FRONT, GL_AMBIENT, (const GLfloat[3]){0.05f, 0.05f, 0.05f});
            glMaterialfv(GL_FRONT, GL_DIFFUSE, (const GLfloat[3]){0.55f, 0.55f, 0.55f});
            glMaterialfv(GL_FRONT, GL_SPECULAR, (const GLfloat[3]){0.870f, 0.870f, 0.870f});
            glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128);
            break;
        case DEFAULT:
            glMaterialfv(GL_FRONT, GL_AMBIENT, (const GLfloat[3]){0.02f, 0.02f, 0.02f});
            glMaterialfv(GL_FRONT, GL_DIFFUSE, (const GLfloat[3]){0.55, 0.55, 0.55});
            glMaterialfv(GL_FRONT, GL_SPECULAR, (const GLfloat[3]){0.870, 0.870, 0.870});
            glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128);
            break;
    }
}

void update_light(GLenum light) {

    switch (light) {
        case GL_LIGHT0: {

            light_bulb_ambient[0] = light_bulb_r * light_bulb_intensity;
            light_bulb_ambient[1] = light_bulb_g * light_bulb_intensity;
            light_bulb_ambient[2] = light_bulb_b * light_bulb_intensity;

            light_bulb_specular[0] = light_bulb_r * light_bulb_intensity;
            light_bulb_specular[1] = light_bulb_g * light_bulb_intensity;
            light_bulb_specular[2] = light_bulb_b * light_bulb_intensity;

            light_bulb_difuse[0] = light_bulb_r * light_bulb_intensity;
            light_bulb_difuse[1] = light_bulb_g * light_bulb_intensity;
            light_bulb_difuse[2] = light_bulb_b * light_bulb_intensity;

            glLightfv(GL_LIGHT0, GL_POSITION, light_bulb_position);
            glLightfv(GL_LIGHT0, GL_AMBIENT, light_bulb_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, light_bulb_difuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_bulb_specular);

            glDisable(GL_LIGHTING);
            glPushMatrix();
            {
                glColor3f(light_bulb_r, light_bulb_g, light_bulb_b);
                glTranslatef(light_bulb_position[0], light_bulb_position[1], light_bulb_position[2]);
                glutSolidSphere(0.5f, 100, 100);
            }
            glPopMatrix();
            glEnable(GL_LIGHTING);

            if (light_bulb_on)
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            break;
        }

        case GL_LIGHT1: {
            // Spot Light
            glLightfv(GL_LIGHT1, GL_POSITION, (const GLfloat *)spotlight_position);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, (const GLfloat *)spotlight_direction);

            glLightfv(GL_LIGHT1, GL_AMBIENT, spotlight_ambient);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_difuse);
            glLightfv(GL_LIGHT1, GL_SPECULAR, spotlight_specular);

            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);

            glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, spotlight_kc);
            glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, spotlight_kl);
            glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, spotlight_kq);

            glDisable(GL_LIGHTING);
            glPushMatrix();
            {
                glColor3f(spotlight_r, spotlight_g, spotlight_b);
                glTranslatef(spotlight_position[0], spotlight_position[1], spotlight_position[2]);
                glutSolidSphere(0.5f, 100, 100);
            }
            glPopMatrix();
            glEnable(GL_LIGHTING);

            if (spotlight_on)
                glDisable(GL_LIGHT1);
            else
                glEnable(GL_LIGHT1);
            break;
        }
    }
}

void update_camera() {
    if (camera[1] > WORLD_XYZ_FAR) camera[1] = WORLD_XYZ_FAR;
    if (camera[1] < -WORLD_XYZ_FAR) camera[1] = -WORLD_XYZ_FAR;

    camera[0] = camera_radius * cos(camera_angle);
    camera[2] = camera_radius * sin(camera_angle);
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

void ascii_keyboard_callback(unsigned char key, int x, int y) {

    switch (toupper(key)) {

        // Open Door
        case '1': {
            //if (door_angle < 90)
            door_angle += ROTATE_SPEED;
            break;
        }

        // Close Door
        case '2': {
            //if (door_angle > 0)
            door_angle -= ROTATE_SPEED;
            break;
        }

        // Open Cat Door
        case '3': {
            if (cat_door_angle < 90)
                cat_door_angle += ROTATE_SPEED;
            break;
        }

        // Close Cat Door
        case '4': {
            if (cat_door_angle > -90)
                cat_door_angle -= ROTATE_SPEED;
            break;
        }

        // Open Door Latch
        case '5': {
            if (handle_angle < 20) {
                handle_angle += ROTATE_SPEED;
                latch_dx += 0.007;
            }
            break;
        }

        // Close Door Latch
        case '6': {
            if (handle_angle > 0) {
                handle_angle -= ROTATE_SPEED;
                latch_dx -= 0.007;
            }
            break;
        }

        // Zoom In
        case 'Z': {
            if (camera_radius > WORLD_XYZ_NEAR) {
                camera_radius -= ZOOM_SPEED;
                update_camera();
            }
            break;
        }

        // Zoom Out
        case 'X':
            camera_radius += ZOOM_SPEED;
            update_camera();
            break;

        // More Light Bulb Red Component
        case 'Q': {
            light_bulb_r += 0.5f;
            break;
        }

        // Less Light Bulb Red Component
        case 'A': {
            light_bulb_r -= 0.5f;
            break;
        }

        // More Light Bulb Green Component
        case 'W': {
            light_bulb_g += 0.5f;
            break;
        }

        // Less Light Bulb Green Component
        case 'S': {
            light_bulb_g -= 0.5f;
            break;
        }

        // More Light Bulb Blue Component
        case 'E': {
            light_bulb_b += 0.5f;
            break;
        }

        // Less Light Bulb Blue Component
        case 'D': {
            light_bulb_b -= 0.5f;
            break;
        }

        // More Light Bulb Intesity
        case 'R': {
            light_bulb_intensity += 0.1f;
            break;
        }

        // Less Light Bulb Intesity
        case 'F': {
            light_bulb_intensity -= 0.1f;
            break;
        }

        // Light Bulb ON/OFF
        case 'B': {
            light_bulb_on = !light_bulb_on;
            break;
        }

        // Spotlight ON/OFF
        case 'N': {
            spotlight_on = !spotlight_on;
            break;
        }

        case 'V': {
            if (ks > 0.05f)
                ks -= 0.05f;
            break;
        }

        case 'C': {
            if (ks < 1.0f)
                ks += 0.05f;
            break;
        }

        case 'H': {
            spotlight_position[0] -= 0.1f;
            break;
        }
        case 'L': {
            spotlight_position[0] += 0.1f;
            break;
        }
        case 'J': {
            spotlight_position[1] -= 0.1f;
            break;
        }
        case 'K': {
            spotlight_position[1] += 0.1f;
            break;
        }

        case 'G': {
            use_grid = !use_grid;
            break;
        }

        case ESC_KEY:
            exit(EXIT_SUCCESS);
            break;
    }
    glutPostRedisplay();
}
