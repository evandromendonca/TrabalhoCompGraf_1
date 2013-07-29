#pragma once

#include <string>
#include <vector>
#include <gl\GLUT.h>

//namespace
using namespace std;


//Defines
#define members
#define functions

#define POINT_ACCURACY_SIZE 5
#define CURVE_ACCURACY_SIZE 10

#define GLUT_KEY_ENTER 13

#define COLOR_RED 1.0, 0.0, 0.0
#define COLOR_GREEN 0.0, 1.0, 0.0
#define COLOR_BLUE 0.0, 0.0, 1.0
#define COLOR_BLACK 0.0, 0.0, 0.0
#define COLOR_WHITE 1.0, 1.0, 1.0

#define GL_WINDOW_SIZE 1024, 768
#define GL_SCREEN 0.0, 1024.0, 768.0, 0.0
#define CENTER_X 512.00f
#define CENTER_Y 384.00f

#define PI 3.141592653589793
#define RAD 180.0


//Enumerators
enum CURVE_TYPE { 
	UNASSIGNED = 0, 
	BEZIER = 1, 
	BSPLINE = 2 
};

enum STATE {
	NO_STATE = 0,
    TYPE_ASSIGNED,
    DEGREE_ASSIGNED,
    TYPE_AND_DEGREE_ASSIGNED,
	CURVE_SELECTED,
	MOVING_CONTROL_POINTS,
	EDITING_CONTROL_POINTS,
	CREATING_BEZIER_CURVE,
	CREATING_BSPLINE,
	SCALING_CURVE,
	TRANSLATING_CURVE,
	ROTATING_CURVE,
	WAITING_BEGIN,
	READING_TYPE,
	READING_DEGREE,
	READING_POINTS,
}; 