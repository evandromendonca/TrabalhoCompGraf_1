#include "beziercurve.h"


BezierCurve::BezierCurve(void) {
	Curve::Curve();
}


BezierCurve::~BezierCurve(void) {

}

void BezierCurve::refresh() {
	m_curvePoints.clear();

	for (float t = 0.0f; t <= 1.0f; t += 0.01f){
		float x = 0.0f, y = 0.0f;

		for (size_t i = 0; i < getControlPoints().size(); i++) {
			x += (float)(getControlPoints()[i].getX() * combination(getCurveDegree(), i) * pow(t, i) * pow( (1.0f - t), (getCurveDegree() - i)));
			y += (float)(getControlPoints()[i].getY() * combination(getCurveDegree(), i) * pow(t, i) * pow( (1.0f - t), (getCurveDegree() - i)));
		}
		
		addCurvePoint(x, y);
	}
}

float BezierCurve::factorial(int value){
	float fact = 1.0;

	for (size_t i = value; i > 0; i--)
		fact *= i;

	return fact;
}

float BezierCurve::combination(int n, int i){
	return factorial(n) / (factorial(i) * factorial(n-i));
}

bool BezierCurve::hasAllControlPoints() { 
	return m_controlPoints.size() == (m_curveDegree + 1);
}

CURVE_TYPE BezierCurve::getType() {
	return BEZIER;
}
