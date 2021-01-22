/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#ifndef __GL_DOOR
#define __GL_DOOR

// Door Settings
extern GLfloat door_angle;
extern GLfloat cat_door_angle;
extern GLfloat handle_angle;
extern GLfloat latch_dx;

void door(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

#endif // __GL_DOOR