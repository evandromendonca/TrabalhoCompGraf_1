#include "beziercurve.h"


BezierCurve::BezierCurve(void) {

}


BezierCurve::~BezierCurve(void) {

}

void BezierCurve::draw() {

}

void BezierCurve::refresh() {
	m_refreshNeeded = false;
}

bool BezierCurve::hasAllControlPoints() { 
	return m_controlPoints.size() == (m_curveDegree - 1);
}

CURVE_TYPE BezierCurve::getType() {
	return BEZIER;
}