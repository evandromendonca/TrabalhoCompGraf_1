#pragma once

#include "curve.h"

class BSpline : public Curve 
{

public:
	BSpline(void);
	~BSpline(void);

	virtual void draw();
	virtual void refresh();

protected:

private:
	vector<Point> m_curvePoints;
};

