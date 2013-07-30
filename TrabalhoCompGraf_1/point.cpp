#include "point.h"


Point::Point(void) {
	m_x = 0.0;
	m_y = 0.0;
}

Point::Point(double x, double y) {
	m_x = x;
	m_y = y;
}

Point::~Point(void) {

}

Point& Point::operator=(const Point &src) {
	m_x = src.m_x;
	m_y = src.m_y;

	return *this;
}

void Point::setPosition(double x, double y) {
	m_x = x;
	m_y = y;
}

void Point::setX(double x) {
	m_x = x;
}

void Point::setY(double y) {
	m_y = y;
}

double Point::getX() {
	return m_x;
}

double Point::getY() {
	return m_y;
}