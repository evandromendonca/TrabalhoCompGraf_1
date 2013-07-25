#include "filehandler.h"
#include "bspline.h"
#include "beziercurve.h"
#include "main.h"
#include <fstream>
#include <sstream>

int getValue(string str) { 
	int value;

	stringstream strStream( str.c_str() );
	strStream >> value;

	return value;
}

bool saveCurves(string fileName) {
	ofstream output;
	output.open(fileName, ios::trunc);
	
	if( output.is_open() ) {
		vector<Curve*> curves = Main::getInstance()->getCurves();

		for (size_t i = 0; i < curves.size(); i++) {
			vector<Point> points = curves.at(i)->getControlPoints();

			output << "BEGIN_CURVE" << endl;
			output << curves.at(i)->getType() << endl;
			output << curves.at(i)->getCurveDegree() << endl;

			for (size_t j = 0; j < points.size(); j++) {
				output << points.at(j).getX() << " " << points.at(j).getY() << endl;
			}
			output << "END_CURVE" << endl;
		}

		output.close();
		return true;
	}

	return false;
}

bool loadCurves(string fileName) {
	ifstream input;
	input.open(fileName, ios::in);
	
	if(input.is_open()) {
		Main *main = Main::getInstance();
		vector<Curve*> curves;
		Curve *curve;
		Point point;
		string buffer = "";	

		while(!input.eof()) { 
			input >> buffer;

			if (buffer == "BEGIN_CURVE") {
				if (main->getState() == WAITING_BEGIN) {
					curve->refresh();
					curves.push_back(curve);
				}
				main->setState(READING_TYPE);
			}
			else if (main->getState() == READING_TYPE) {
				if (buffer == "1")	
					curve = new BezierCurve();
				else
					curve = new BSpline();

				main->setState(READING_DEGREE);
			}
			else if (main->getState() == READING_DEGREE) {
				curve->setCurveDegree(getValue(buffer));

				main->setState(READING_POINTS);
			}
			else if (main->getState() == READING_POINTS) {
				if (buffer == "END_CURVE")
					main->setState(WAITING_BEGIN);
				else {
					point.setX(getValue(buffer));

					input >> buffer;
					point.setY(getValue(buffer));

					curve->addControlPoint(point);
				}
			}
		}

		curve->refresh();
		curves.push_back(curve);
		main->setCurves(curves);
		main->setState(NO_STATE);
		input.close();
		return true;
	}

	return false;
}