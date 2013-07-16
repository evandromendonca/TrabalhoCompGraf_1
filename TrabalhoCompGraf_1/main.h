#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include <gl\glut.h>

using namespace std;

enum CURVE_TYPE { Bezier = 1, BSpline = 2 };


//Members
static int window;
int menuID;
int curveTypeSubMenuID;
int curveDegreeSubMenuID;

CURVE_TYPE curveType;
int curveDegree;
int selectedCurve;

//Functions
void menu(int);
void createMenu(void);

void idle();
void display(void);