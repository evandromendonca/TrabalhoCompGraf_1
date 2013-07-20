#pragma once

#include "curve.h"

class BSpline : public Curve 
{

public:
	BSpline(void);
	~BSpline(void);

	virtual void draw();
	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

protected:

private:
	vector<Point> m_curvePoints;
};

