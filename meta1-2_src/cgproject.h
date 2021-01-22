/**
 * Licenciatura em Engenharia Informática | Faculdade de Ciências e Tecnologia da Universidade de Coimbra
 * Projeto de Computação Gráfica - Porta 2020/2021
 *
 * 2018283166 Pedro Miguel Duque Rodrigues
 *   
*/

#ifndef __CG_PROJECT_PCH
#define __CG_PROJECT_PCH

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "RgbImage.h"
#include "door.h"
#include "utils.h"

// World Settings
#define CANVAS_WIDTH 1800
#define CANVAS_HEIGHT 1200

#define WORLD_XYZ_NEAR 0.1f
#define WORLD_XYZ_FAR 100.0f

// ASCII key code
#define ESC_KEY 27

#define TO_RADIANS(ANGLE) M_PI *ANGLE / 180.0f

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

// Speeds

#define CAMERA_FOV_Y (GLfloat)95
#define CAMERA_FOV_X (GLfloat)(CANVAS_WIDTH / CANVAS_HEIGHT)

#define CAMERA_SPEED 0.5f
#define ZOOM_SPEED 0.5f
#define ANGLE_SPEED 0.1f
#define ROTATE_SPEED 1.0f

extern GLuint texture[6];

#endif // __CG_PROJECT_PCH