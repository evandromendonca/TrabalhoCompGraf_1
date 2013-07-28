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

void Curve::setControlPoints(vector<Point> points) {
	m_controlPoints.clear();

	for (size_t i = 0; i < points.size(); i++) {
		m_controlPoints.push_back(points.at(i));
	}
}

void Curve::addCurvePoint(Point point) {
	m_curvePoints.push_back(point);
}

void Curve::addCurvePoint(float x, float y) {
	m_curvePoints.push_back(Point(x, y));
}

void Curve::translateCurve(Point mouseMoveDistance) {

	if (mouseMoveDistance.getX() != 0 || mouseMoveDistance.getY() != 0) {
		for (size_t i = 0; i < m_controlPoints.size() ; i++)
		{
			m_controlPoints.at(i).setX( (int)m_controlPoints.at(i).getX() + mouseMoveDistance.getX() ); 
			m_controlPoints.at(i).setY( (int)m_controlPoints.at(i).getY() + mouseMoveDistance.getY() );			
		}

		refresh();
	}
}
void Curve::rotateCurve(Point mouseMoveDistance) {
	if (mouseMoveDistance.getX() != 0) {
		for (size_t i = 0; i < m_controlPoints.size() ; i++)
		{
			//ERRO AO REESCALAR, PROVAVELMENTE PELO TYPE CASTING, ESTÁ DIMINUINDO O TAMANHO DA CURVA
			//TESTES DE MUDANÇA DE REFERENCIA
			m_controlPoints.at(i).setPosition(m_controlPoints.at(i).getX() - 512.00f, m_controlPoints.at(i).getY() - 384.00f);

			m_controlPoints.at(i).setX( m_controlPoints.at(i).getX() * cos((mouseMoveDistance.getX()/180)*PI) - m_controlPoints.at(i).getY() * sin((mouseMoveDistance.getX()/180)*PI) ); 
			m_controlPoints.at(i).setY( m_controlPoints.at(i).getX() * sin((mouseMoveDistance.getX()/180)*PI) + m_controlPoints.at(i).getY() * cos((mouseMoveDistance.getX()/180)*PI) );

			m_controlPoints.at(i).setPosition(m_controlPoints.at(i).getX() + 512.00f, m_controlPoints.at(i).getY() + 384.0f);
		}

		refresh();
	}
}
void Curve::escaleCurve(Point mouseMoveDistance) {
	if (mouseMoveDistance.getX() != 0) {

		float x = m_controlPoints.at(0).getX(), y = m_controlPoints.at(0).getY();
		
		float multiplicativeFactor = mouseMoveDistance.getX() > 0 ? 1.05 : 0.95;


		for (size_t i = 0; i < m_controlPoints.size() ; i++)
		{
			m_controlPoints.at(i).setPosition(m_controlPoints.at(i).getX() - x, m_controlPoints.at(i).getY() - y);

			m_controlPoints.at(i).setX( m_controlPoints.at(i).getX() * multiplicativeFactor); 
			m_controlPoints.at(i).setY( m_controlPoints.at(i).getY() * multiplicativeFactor);				

			m_controlPoints.at(i).setPosition(m_controlPoints.at(i).getX() + x, m_controlPoints.at(i).getY() + y);
		}

		refresh();
	}
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
