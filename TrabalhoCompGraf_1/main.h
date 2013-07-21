#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


#include <gl\glut.h>

#include "beziercurve.h"
#include "bspline.h"

using namespace std;


enum STATE {
	NO_STATE = 0,
    TYPE_ASSIGNED,
    DEGREE_ASSIGNED,
    TYPE_AND_DEGREE_ASSIGNED,
	CURVE_SELECTED,
	EDITING_CONTROL_POINTS,
	CREATING_CURVE,
	SCALING_CURVE,
	TRANSLATING_CURVE,
	ROTATING_CURVE,
	WAITING_BEGIN,
	READING_TYPE,
	READING_DEGREE,
	READING_POINTS,
}; 


//Members
static int window;
STATE currentState;
int menuID;
int curveTypeSubMenuID;
int curveDegreeSubMenuID;
int curveOptionsSubMenuID;

CURVE_TYPE typeAssigned;
int degreeAssigned;

Curve *currentCurve;
int selectedCurveIndex;

vector<Curve*> curves;

//Functions
int getValue(string);
void saveCurves(string);
void loadCurves(string);
void menu(int);
void createMenu(void);

void init();
void idle();
void mouse();
void display(void);

