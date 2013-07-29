#pragma once

#include "curve.h"

class Main
{

public functions:
	Main(void);
	static Main* getInstance();
	int run(int, char**);

	vector<Curve*> getCurves();
	void setCurves(vector<Curve*>);
	void addCurve(Curve*);

	STATE getState();
	void setState(STATE);

	Curve* getCurrentCurve();
	void setCurrentCurve(Curve*);
	void addPointToCurrentCurve(Point);
	void addPointToCurrentCurve(float, float);
	void setCurrentCurveDegree(int);
	void refreshCurrentCurve();

	int getSelectedCurve();
	void setSelectedCurve(int);

	int getSelectedPoint();
	void setSelectedPoint(int);

	int getAssignedDegree();
	void setAssignedDegree(int);

	CURVE_TYPE getAssignedType();
	void setAssignedType(CURVE_TYPE);

	void deleteCurve();

	void createMenu();

private members:
	static Main *m_instance;
	vector<Curve*> m_curves;

	STATE m_currentState;
	Curve *m_pCurrentCurve;
	int m_selectedCurve;
	int m_selectedPoint;

	int m_window;
	int m_menuID;
	int m_curveTypeSubMenuID;
	int m_curveDegreeSubMenuID;
	int m_curveOptionsSubMenuID;

	int m_assignedDegree;
	CURVE_TYPE m_assignedType;

};
