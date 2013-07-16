#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <gl\glut.h>

using namespace std;

enum CURVE_TYPE { NotSelected = -1, Bezier = 1, BSpline = 2 };

typedef struct _Point {
	float x;
	float y;

	_Point() {
		x = 0.0;
		y = 0.0;
	}

	_Point(int xValue, int yValue) {
		x = xValue;
		y = yValue;
	}

	_Point& operator=(const _Point &src) {
		x = src.x;
		y = src.y;
	}
} Point;

typedef struct _Curve {
	vector<Point> points;
	CURVE_TYPE curveType;
	int curveDegree;

	_Curve() {
		curveType = NotSelected;
		curveDegree = -1;
	}

	_Curve& operator=(const _Curve &src) {
		points.clear();
		points = src.points;
		curveDegree = src.curveDegree;
		curveType = src.curveType;
	}

} Curve;


//Members
static int window;
int menuID;
int curveTypeSubMenuID;
int curveDegreeSubMenuID;

Curve *currentCurve;

bool drawingCurve;

//Functions
void menu(int);
void createMenu(void);

void init();

void idle();
void mouse();
void display(void);


vector<Curve*> curves;