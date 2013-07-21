#pragma once

#include "curve.h"

class BezierCurve : public Curve 
{

public:
	BezierCurve(void);
	~BezierCurve(void);

	virtual void draw();
	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

protected:


private:
	float factorial(int);
	float combination(int, int);
};