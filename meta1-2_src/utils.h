/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#ifndef __GL_UTILS
#define __GL_UTILS

#include <stdbool.h>

extern GLdouble camera[3];

// Light Bulb - GL_LIGHT0
extern bool light_bulb_on;
extern GLfloat light_bulb_position[4];
extern GLfloat light_bulb_intensity;
extern GLfloat light_bulb_r, light_bulb_g, light_bulb_b;

// Spot Light - GL_LIGHT1
extern bool spotlight_on;
extern GLfloat spotlight_position[4];
extern GLfloat spotlight_direction[4];
extern GLfloat spotlight_intensity;
extern GLfloat spotlight_r, spotlight_g, spotlight_b;

// Door Handle Specular component
extern GLfloat ks;
extern bool use_grid;

// Materials
typedef enum Material {
    CHROME,
    PLASTIC,
    DEFAULT,
} material_t;

void ascii_keyboard_callback(unsigned char key, int x, int y);
void non_ascii_keyboard_callback(int key, int x, int y);

void debug_axis();
void draw_circle(GLfloat x, GLfloat y, GLfloat z, int radius);
void draw_cylinder(GLfloat radius, GLfloat height);
void draw_cube(GLfloat side, bool use_square_grid);

void setup_lights();
void load_texture(GLuint *texture_id, const char *texture_file);
void select_material(material_t index);
void update_light(GLenum light);

#endif // __GL_UTILS3