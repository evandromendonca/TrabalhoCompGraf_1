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
	vector<float> knots;

	float basis(int, int, float);
	void createKnotsVetor(int, int, int);

};

