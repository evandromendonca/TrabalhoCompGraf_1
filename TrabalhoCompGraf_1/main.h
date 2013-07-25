#pragma once

#include "curve.h"

class Main
{

public members:
	static Curve *m_pCurrentCurve;
	static STATE m_currentState;
	static CURVE_TYPE m_typeAssigned;
	static int m_degreeAssigned;
	static int m_selectedCurveIndex;
	static int m_menuID;
	static int m_curveTypeSubMenuID;
	static int m_curveDegreeSubMenuID;
	static int m_curveOptionsSubMenuID;

public functions:
	Main(void);
	static Main* getInstance();
	void run(int, char**);
	void initialize();

	vector<Curve*> getCurves();
	void setCurves(vector<Curve*>);
	void addCurve(Curve*);

	STATE getState();
	void setState(STATE);

	void createMenu();

private members:
	static Main *m_instance;
	int m_window;
	vector<Curve*> m_curves;

};
