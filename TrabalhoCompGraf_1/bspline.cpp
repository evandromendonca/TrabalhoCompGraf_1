#include "bspline.h"


BSpline::BSpline(void) {

}


BSpline::~BSpline(void) {

}

void BSpline::draw() {

}

void BSpline::refresh() {
	m_refreshNeeded = false;
}

bool BSpline::hasAllControlPoints() { 
	return m_controlPoints.size() == (m_curveDegree + 1);
}

CURVE_TYPE BSpline::getType() {
	return BSPLINE;
}