#pragma once

#include "types.h"

functions
	int checkControlPointHit(int x, int y);
	int checkCurveHit(int x, int y);
	void mouse(int, int, int, int);
	void mouseMotion(int, int);

	void drawControlPoints();
	void display(void);

	void keyboard(unsigned char, int, int);

	void menu(int);
