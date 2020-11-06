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
#define CAMERA_SPEED 0.1f
#define ZOOM_SPEED 0.1f
#define ANGLE_SPEED 0.1f
#define ROTATE_SPEED 1.0f

#endif // __CG_PROJECT_PCH