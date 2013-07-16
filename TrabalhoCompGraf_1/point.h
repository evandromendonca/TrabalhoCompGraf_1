#pragma once

class Point
{

public:
	Point(void);
	Point(float, float);
	~Point(void);

	Point& operator=(const Point&);

	void setX(float);
	void setY(float);

	float getX();
	float getY();

protected:

private:
	float m_x;
	float m_y;

};

