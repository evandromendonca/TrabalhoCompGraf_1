#pragma once

#include "curve.h"

class BezierCurve : public Curve 
{

public:
	BezierCurve(void);
	~BezierCurve(void);

	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

protected:


private:
	double factorial(int);
	double combination(int, int);
};