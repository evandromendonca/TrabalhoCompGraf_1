#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <gl\glut.h>

#include "curve.h"

using namespace std;

enum CURVE_TYPE { NotSelected = -1, Bezier = 1, BSpline = 2 };

enum STATE {
	NO_STATE = 0,
	CURVE_SELECTED,
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

Curve *currentCurve;

//Functions
void menu(int);
void createMenu(void);

void init();

void idle();
void mouse();
void display(void);


vector<Curve*> curves;