#pragma once

#include "curve.h"

class BezierCurve : public Curve 
{

public:
	BezierCurve(void);
	~BezierCurve(void);

	virtual void draw();
	virtual void refresh();

protected:


private:
	vector<Point> m_curvePoints;

};

