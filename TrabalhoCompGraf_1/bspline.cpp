#include "bspline.h"


BSpline::BSpline(void) {
	Curve::Curve();
}


BSpline::~BSpline(void) {

}

void BSpline::refresh() {
	m_curvePoints.clear();
}

bool BSpline::hasAllControlPoints() { 
	return m_controlPoints.size() == (m_curveDegree + 1);
}

CURVE_TYPE BSpline::getType() {
	return BSPLINE;
}