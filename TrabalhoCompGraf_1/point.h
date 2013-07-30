#pragma once

class Point
{

public:
	Point(void);
	Point(double, double);
	~Point(void);

	Point& operator=(const Point&);

	void Point::setPosition(double x, double y);

	void setX(double);
	void setY(double);

	double getX();
	double getY();

protected:

private:
	double m_x;
	double m_y;

};