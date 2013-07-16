#include "point.h"


Point::Point(void) {
	m_x = 0.0;
	m_y = 0.0;
}

Point::Point(float x, float y) {
	m_x = x;
	m_y = x;
}

Point::~Point(void) {

}

Point& Point::operator=(const Point &src) {
	m_x = src.m_x;
	m_y = src.m_y;

	return *this;
}

void Point::setX(float x) {
	m_x = x;
}

void Point::setY(float y) {
	m_y = y;
}

float Point::getX() {
	return m_x;
}

float Point::getY() {
	return m_y;
}


