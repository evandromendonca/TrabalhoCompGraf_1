#include "curve.h"


Curve::Curve(void) {
	m_curveDegree = -1;
}

Curve& Curve::operator=(const Curve &src) {
	m_controlPoints.clear();
	m_controlPoints = src.m_controlPoints;
	m_curveDegree = src.m_curveDegree;

	return *this;
}

Curve::~Curve(void) {

}

void Curve::draw(GLfloat r, GLfloat g, GLfloat b) {

	//Begin drawing curves
	glColor3f(r, g, b);			//Set curve color
	glBegin(GL_LINES);
	for (size_t j = 0; j < m_curvePoints.size() - 1; j++) {
		glVertex2f(m_curvePoints[j].getX(), m_curvePoints[j].getY());
		glVertex2f(m_curvePoints[j+1].getX(), m_curvePoints[j+1].getY());
	}
	glEnd();
	//End drawing curves
}


void Curve::refresh() {

}

bool Curve::hasAllControlPoints() { 
	return m_controlPoints.size() == m_curveDegree;
}

void Curve::setCurveDegree(int curveDegree) {
	m_curveDegree = curveDegree;
}

int Curve::getCurveDegree() {
	return m_curveDegree;
}

void Curve::addControlPoint(Point point) {
	m_controlPoints.push_back(point);
}

void Curve::addControlPoint(float x, float y) {
	m_controlPoints.push_back(Point(x, y));
}

void Curve::addCurvePoint(Point point) {
	m_curvePoints.push_back(point);
}

void Curve::addCurvePoint(float x, float y) {
	m_curvePoints.push_back(Point(x, y));
}

vector<Point> Curve::getControlPoints() {
	return m_controlPoints;
}

vector<Point> Curve::getCurvePoints() {
	return m_curvePoints;
}

CURVE_TYPE Curve::getType() {
	return UNASSIGNED;
}
