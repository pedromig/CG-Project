#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>

// World Settings
#define CANVAS_WIDTH 1800
#define CANVAS_HEIGHT 1200

#define WORLD_XYZ_NEAR 0.1f
#define WORLD_XYZ_FAR 100.0f

#define CAMERA_FOV_Y (GLfloat)95
#define CAMERA_ASPECT_RATIO (GLfloat)(CANVAS_WIDTH / CANVAS_HEIGHT)

#define CAMERA_SPEED 0.5f
#define ZOOM_SPEED 0.5f
#define ANGLE_SPEED 0.1f

// Standard Colors
#define BLUE 0.0f, 0.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f, 1.0f
#define GREEN 0.0f, 1.0f, 0.0f, 1.0f
#define ORANGE 1.0f, 0.5f, 0.1f, 1.0f
#define CYAN 0.0f, 1.0f, 1.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f, 1.0f
#define BLACK 0.0f, 0.0f, 0.0f, 1.0f
#define GRAY 0.3f, 0.3f, 0.3f, 1.0f
#define BROWN 0.6f, 0.3f, 0.0f, 1.0f

// Camer Settings
GLfloat camera_radius = 25.0f;
GLfloat camera_angle = (GLfloat)M_PI_2;
GLfloat light_angle = (GLfloat)M_PI_2;
GLfloat light_vertical = 0.0f;
GLfloat camera[] = {
    camera_radius * (GLfloat)cos(camera_angle),
    20.0f,
    camera_radius *(GLfloat)sin(camera_angle),
};
GLfloat light_direction[] = {
    (GLfloat)cos(light_angle),
    (GLfloat)-sin(light_vertical),
    (GLfloat)sin(light_angle),
};

// Shader Ids
GLuint phong_shading;
GLuint gouraud_shading;

GLuint create_shader(std::string const &shader_path, GLenum const shader_type) {

    try {
        std::ifstream shader_file(shader_path);
        std::stringstream buffer;

        buffer << shader_file.rdbuf();
        std::string shader_source = buffer.str();
        shader_file.close();

        GLuint shader;
        if (!(shader = glCreateShader(shader_type))) {
            std::cerr << "Error creating shader " << shader << "..." << std::endl;
            std::cerr << "Aborting..." << std::endl;
            std::abort();
        }

        const GLchar *source = static_cast<const GLchar *>(shader_source.c_str());
        glShaderSource(shader, 1, &source, NULL);
        glCompileShaderARB(shader);

        GLint compiled_successfully;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled_successfully);
        if (!compiled_successfully) {
            std::cerr << "Error compiling shader " << shader_path << std::endl;
            std::cerr << "Aborting..." << std::endl;
            std::abort();
        }

        return shader;

    } catch (std::ifstream::failure const &e) {
        std::cerr << "Exception occurred while opening shader file..." << std::endl;
        std::cerr << e.what() << std::endl;
        std::cerr << "Aborting..." << std::endl;
        std::abort();
    }
}

inline GLuint new_shader_program(GLuint const vertex_shader, GLuint const fragment_shader) {
    GLuint program = glCreateProgramObjectARB();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    return program;
}

inline void delete_shader_program(GLuint const program, GLuint const fragment_shader, GLuint const vertex_shader) {
    glDetachShader(program, fragment_shader);
    glDetachShader(program, vertex_shader);
    glDeleteShader(program);
}

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
void update_camera() {
    if (camera[1] > WORLD_XYZ_FAR) camera[1] = WORLD_XYZ_FAR;
    if (camera[1] < -WORLD_XYZ_FAR) camera[1] = -WORLD_XYZ_FAR;

    camera[0] = (GLfloat)(camera_radius * cos(camera_angle));
    camera[2] = (GLfloat)(camera_radius * sin(camera_angle));
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

        case 'Z': {
            if (camera_radius > WORLD_XYZ_NEAR) {
                camera_radius -= ZOOM_SPEED;
                update_camera();
            }
            break;
        }

        case 'X':
            camera_radius += ZOOM_SPEED;
            update_camera();
            break;

        case 'D': {
            light_angle += ANGLE_SPEED;
            light_direction[0] = (GLfloat)cos(light_angle);
            light_direction[2] = (GLfloat)sin(light_angle);
            break;
        }

        case 'A': {
            light_angle -= ANGLE_SPEED;
            light_direction[0] = (GLfloat)cos(light_angle);
            light_direction[2] = (GLfloat)sin(light_angle);
            break;
        }

        case 'W': {
            light_vertical += ANGLE_SPEED;
            light_direction[1] = (GLfloat)sin(light_vertical);
            break;
        }

        case 'S': {
            light_vertical -= ANGLE_SPEED;
            light_direction[1] = (GLfloat)sin(light_vertical);
            break;
        }
    }
    glutPostRedisplay();
}

void draw_callback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 500, 500);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(CAMERA_FOV_Y, CAMERA_ASPECT_RATIO, WORLD_XYZ_NEAR, WORLD_XYZ_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera[0], camera[1], camera[2], 0, 10, 0, 0, 1, 0);

    glUseProgramObjectARB(phong_shading);
    auto camera_position = glGetUniformLocation(phong_shading, "camera");
    auto light_dir = glGetUniformLocation(phong_shading, "light_direction");

    glUniform3fv(light_dir, 1, light_direction);
    glUniform3fv(camera_position, 1, camera);

    glPushMatrix();
    {
        glTranslatef(15, 10, 0);
        glutSolidSphere(10, 30, 30);
    }
    glPopMatrix();

    glUseProgramObjectARB(gouraud_shading);
    camera_position = glGetUniformLocation(gouraud_shading, "camera");
    light_dir = glGetUniformLocation(gouraud_shading, "light_direction");

    glUniform3fv(light_dir, 1, light_direction);
    glUniform3fv(camera_position, 1, camera);

    glPushMatrix();
    {
        glTranslatef(-15, 10, 0);
        glutSolidSphere(10, 30, 30);
    }
    glPopMatrix();

#ifdef DEBUG
    glUseProgramObjectARB(0);
    debug_axis();
#endif

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("CG Project - Shaders");

    glClearColor(BLACK);
    glEnable(GL_DEPTH_TEST);

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed" << std::endl;
        std::abort();
    }

    // Phong Shader Program
    auto phong_fragment_shader = create_shader("../shaders/phong_fragment_shader.frag", GL_FRAGMENT_SHADER);
    auto phong_vertex_shader = create_shader("../shaders/phong_vertex_shader.vert", GL_VERTEX_SHADER);

    phong_shading = new_shader_program(phong_fragment_shader, phong_vertex_shader);
    delete_shader_program(phong_shading, phong_fragment_shader, phong_vertex_shader);

    // Gouraud Shader Program
    auto gouraud_fragment_shader = create_shader("../shaders/gouraud_fragment_shader.frag", GL_FRAGMENT_SHADER);
    auto gouraud_vertex_shader = create_shader("../shaders/gouraud_vertex_shader.vert", GL_VERTEX_SHADER);

    gouraud_shading = new_shader_program(gouraud_fragment_shader, gouraud_vertex_shader);
    delete_shader_program(gouraud_shading, gouraud_fragment_shader, gouraud_vertex_shader);

    glutDisplayFunc(draw_callback);
    glutSpecialFunc(non_ascii_keyboard_callback);
    glutKeyboardFunc(ascii_keyboard_callback);

    glutMainLoop();
    return EXIT_SUCCESS;
}