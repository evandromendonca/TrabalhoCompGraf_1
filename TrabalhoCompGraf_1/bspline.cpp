#include "bspline.h"


BSpline::BSpline(void) {
	Curve::Curve();
}


BSpline::~BSpline(void) {

}

void BSpline::refresh() {
	m_curvePoints.clear();

	createKnotsVector(m_curveDegree, m_controlPoints.size() - 1, (size_t)m_controlPoints.size() + m_curveDegree);

	for(double iterator = m_knots.at(m_curveDegree-1); iterator <= m_knots.at(m_controlPoints.size()); iterator += 0.01f) {
		double x = 0.0f, y = 0.0f;

		for(size_t i = 0; i < m_controlPoints.size(); i++) {
			double base = basis(i, m_curveDegree, iterator);
			x += base * getControlPoints().at(i).getX();
			y += base * getControlPoints().at(i).getY();
		}

		addCurvePoint(x,y);
	}

	Curve::refresh();
}

bool BSpline::hasAllControlPoints() { 
	return m_controlPoints.size() >= (m_knots.size() - m_curveDegree - 1);
}

CURVE_TYPE BSpline::getType() {
	return BSPLINE;
}

void BSpline::createKnotsVector(int p, int n, size_t m) {
	double iterator = 0.0;
	for (size_t i = 0; i <= m; i++) {
		m_knots.push_back(iterator);
		iterator += 1.0f/(double)m;
	}
	
}

double BSpline::basis(int i, int j, double t) {

	if( j == 1 ) {
		if( (m_knots.at(i) <= t && t < m_knots.at(i+1)) )
			return 1;
		return 0;
	}

	double numeratorA = ( t - m_knots.at(i) );
	double denominatorA = ( m_knots.at(i + j - 1) - m_knots.at(i) );
	double numeratorB = ( m_knots.at(i + j) - t );
	double denominatorB = ( m_knots.at(i + j) - m_knots.at(i + 1) );

	double subweightA = 0;
	double subweightB = 0;

	if( denominatorA != 0 )
		subweightA = (numeratorA / denominatorA) * basis(i, j-1, t);
	if( denominatorB != 0 )
		subweightB = (numeratorB / denominatorB) * basis(i+1, j-1, t);

	return subweightA + subweightB;
}
