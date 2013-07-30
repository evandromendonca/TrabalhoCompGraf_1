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

	void setControlPoints(vector<Point>);

	void addControlPoint(Point);
	void addControlPoint(double, double);
	void addCurvePoint(Point);
	void addCurvePoint(double, double);

	void moveControlPoint(double, double, int);
	void translateCurve(Point);
	void rotateCurveScreen(Point);
	void rotateCurveAxis(Point);
	void scaleCurve(Point);

	int getCurveDegree();
	Point getCenter();
	vector<Point> getControlPoints();
	vector<Point> getCurvePoints();

protected:
	vector<Point> m_controlPoints;
	vector<Point> m_curvePoints;
	int m_curveDegree;
	Point m_center;

private:

};