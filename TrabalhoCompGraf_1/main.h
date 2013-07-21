#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
int menuID;
int curveTypeSubMenuID;
int curveDegreeSubMenuID;
int curveOptionsSubMenuID;

vector<Curve*> curves;

STATE currentState;
Curve *currentCurve;

CURVE_TYPE typeAssigned;
int degreeAssigned;

int selectedCurveIndex;


//Functions
int getValue(string);
void saveCurves(string);
void loadCurves(string);
void menu(int);
void createMenu(void);
int checkCurveHit(int, int);
void drawControlPoints();

void init();
void idle();
void mouse();
void display(void);

