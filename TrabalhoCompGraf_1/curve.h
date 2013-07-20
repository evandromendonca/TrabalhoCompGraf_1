#pragma once


#include "point.h"
#include <vector>

enum CURVE_TYPE { UNASSIGNED = 0, BEZIER = 1, BSPLINE = 2 };

using namespace std;

class Curve
{

public:
	Curve(void);
	~Curve(void);

	Curve& operator=(const Curve&);

	virtual void draw();
	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

	void setCurveDegree(int);
	void addControlPoint(Point);
	void addControlPoint(float, float);

	int getCurveDegree();
	vector<Point> getControlPoints();

protected:
	vector<Point> m_controlPoints;
	int m_curveDegree;
	bool m_refreshNeeded;

private:

};