#include "bspline.h"


BSpline::BSpline(void) {
	Curve::Curve();
}


BSpline::~BSpline(void) {

}

void BSpline::refresh() {
	m_curvePoints.clear();

	createKnotsVector(m_curveDegree, m_controlPoints.size() - 1, m_controlPoints.size() + m_curveDegree);

	for(float iterator = 0.0f; iterator < 1; iterator += 0.01f)
	{
		float x = 0.0f, y = 0.0f;

		for(size_t i = 0; i < m_controlPoints.size(); i++)
		{
			float base = basis(i, m_curveDegree, iterator);
			x += base * getControlPoints().at(i).getX();
			y += base * getControlPoints().at(i).getY();
		}

		addCurvePoint(x,y);
	}
}

bool BSpline::hasAllControlPoints() { 
	return m_controlPoints.size() >= (m_knots.size() - m_curveDegree - 1);
}

CURVE_TYPE BSpline::getType() {
	return BSPLINE;
}

void BSpline::createKnotsVector(int p, int n, int m) {
	for (float i = 0; i <= p; i++)
		m_knots.push_back(0);
	
	float j = 0;
	for (float i = p+1; i <= (m-p-1); i++){
		j++;
		m_knots.push_back( j / ( n - p + 1 ) );
	}

	for (float i = (m-p); i <= m; i++)
		m_knots.push_back(1);
}

float BSpline::basis(int i, int j, float t) {

	if( j == 0 ) {
		if( (m_knots.at(i) <= t && t < m_knots.at(i+1)) && (m_knots.at(i) < m_knots.at(i+1)) )
			return 1;
		else
			return 0;
	} 

	float numeratorA = ( t - m_knots.at(i) );
	float denominatorA = ( m_knots.at(i + j) - m_knots.at(i) );
	float numeratorB = ( m_knots.at(i + j + 1) - t );
	float denominatorB = ( m_knots.at(i + j + 1) - m_knots.at(i + 1) );

	float subweightA = 0;
	float subweightB = 0;

	if( denominatorA != 0 )
		subweightA = (numeratorA / denominatorA) * basis(i, j-1, t);
	if( denominatorB != 0 )
		subweightB = (numeratorB / denominatorB) * basis(i+1, j-1, t);

	return subweightA + subweightB;
}
