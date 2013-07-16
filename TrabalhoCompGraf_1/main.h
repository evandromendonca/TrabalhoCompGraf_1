#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <gl\glut.h>

#include "beziercurve.h"
#include "bspline.h"

using namespace std;

enum CURVE_TYPE { UNASIGNED = 0, BEZIER = 1, BSPLINE = 2 };

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

//Functions
void saveCurves(string);
void loadCurves(string);
void menu(int);
void createMenu(void);

void init();

void idle();
void mouse();
void display(void);


vector<Curve*> curves;