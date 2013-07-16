#pragma once

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <gl\glut.h>

#include "beziercurve.h"
#include "bspline.h"

using namespace std;

enum CURVE_TYPE { Bezier = 1, B_Spline = 2 };

enum STATE {
	NO_STATE = 0,
    TYPE_ASSIGNED,
    DEGREE_ASSIGNED,
    TYPE_AND_DEGREE_ASSIGNED,
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

CURVE_TYPE typeAssigned;
int degreeAssigned;

Curve *currentCurve;

//Functions
void menu(int);
void createMenu(void);

void init();

void idle();
void mouse();
void display(void);


vector<Curve*> curves;