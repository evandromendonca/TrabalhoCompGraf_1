#include "beziercurve.h"


BezierCurve::BezierCurve(void) {
	Curve::Curve();
}

BezierCurve::~BezierCurve(void) {

}

void BezierCurve::refresh() {

	m_curvePoints.clear();

	for (double t = 0.0f; t <= 1.0f; t += 0.01f){
		double x = 0.0f, y = 0.0f;

		for (size_t i = 0; i < getControlPoints().size(); i++) {
			x += (double)(getControlPoints()[i].getX() * combination(getCurveDegree(), i) * pow(t, i) * pow( (1.0f - t), (getCurveDegree() - i)));
			y += (double)(getControlPoints()[i].getY() * combination(getCurveDegree(), i) * pow(t, i) * pow( (1.0f - t), (getCurveDegree() - i)));
		}
		
		addCurvePoint(x, y);
	}

	Curve::refresh();
}

double BezierCurve::factorial(int value){
	double fact = 1.0;

	for (size_t i = value; i > 0; i--)
		fact *= i;

	return fact;
}

double BezierCurve::combination(int n, int i){
	return factorial(n) / (factorial(i) * factorial(n-i));
}

bool BezierCurve::hasAllControlPoints() { 
	return m_controlPoints.size() == (m_curveDegree + 1);
}

CURVE_TYPE BezierCurve::getType() {
	return BEZIER;
}