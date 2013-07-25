#pragma once

#include "types.h"
#include "point.h"


class Curve
{

public:
	Curve(void);
	~Curve(void);

	Curve& operator=(const Curve&);

	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

	void draw(GLfloat, GLfloat, GLfloat);
	void setCurveDegree(int);
	void addControlPoint(Point);
	void addControlPoint(float, float);
	void addCurvePoint(Point);
	void addCurvePoint(float, float);

	int getCurveDegree();
	vector<Point> getControlPoints();
	vector<Point> getCurvePoints();

protected:
	vector<Point> m_controlPoints;
	vector<Point> m_curvePoints;
	int m_curveDegree;

private:

};