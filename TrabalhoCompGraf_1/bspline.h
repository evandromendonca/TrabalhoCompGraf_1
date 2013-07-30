#pragma once

#include "curve.h"

class BSpline : public Curve 
{

public:
	BSpline(void);
	~BSpline(void);

	virtual void refresh();
	virtual bool hasAllControlPoints();
	virtual CURVE_TYPE getType();

protected:

private:
	vector<double> m_knots;

	double basis(int, int, double);
	void createKnotsVector(int, int, size_t);

};

