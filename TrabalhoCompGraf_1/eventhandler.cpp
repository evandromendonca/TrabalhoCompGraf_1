#include "eventhandler.h"
#include "filehandler.h"
#include "beziercurve.h"
#include "bspline.h"
#include "main.h"

#include <iostream>

//Curve Selection
int checkCurveHit(int x, int y) {
	vector<Curve*> curves = Main::getInstance()->getCurves();
	
	for (size_t i = 0; i < curves.size(); i++) {
		vector<Point> points = curves.at(i)->getCurvePoints();

		for (size_t j = 0; j < points.size(); j++) {
			//Declarei constantes só para facilitar a leitura (evandromendonca)
			if ( (x > (points.at(j).getX() - ACCURACY_SIZE) && x < (points.at(j).getX() + ACCURACY_SIZE)) && 
				 (y > (points.at(j).getY() - ACCURACY_SIZE) && y < (points.at(j).getY() + ACCURACY_SIZE)) )
				return i;
		}
	}
	return -1;
}

//Mouse Event
void mouse(int button, int state, int x, int y) {
	Main *main = Main::getInstance();

	//Creating initial control points of the curve
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (main->getState() == CREATING_BEZIER_CURVE || main->getState() == CREATING_BSPLINE))
		main->addPointToCurrentCurve(x, y);
	
	//Adding bezier curve to the list and generating curve points
	if (main->getState() == CREATING_BEZIER_CURVE && main->getCurrentCurve()->hasAllControlPoints()) {
		main->refreshCurrentCurve();
		main->addCurve(main->getCurrentCurve());
		main->setState(NO_STATE);
	}

	//Checking selection of a curve
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (main->getState() == NO_STATE || main->getState() == CURVE_SELECTED)) {
		main->setSelectedCurve(checkCurveHit(x, y));

		if ( main->getSelectedCurve() != -1) {
			main->setCurrentCurve(main->getCurves().at(main->getSelectedCurve()));
			main->setState(CURVE_SELECTED);
			main->createMenu();
		}
		else {
			main->setCurrentCurve(new Curve());
			main->setState(NO_STATE);
			main->createMenu();
		}
	}

	//Other cases
    glutPostRedisplay();
}


//Drawing Control Points Event
void drawControlPoints() {
	glColor3f(COLOR_BLUE);

	glBegin(GL_POINTS);

	vector<Point> points = Main::getInstance()->getCurrentCurve()->getControlPoints();

	//Draw only the control points of the current curve
	for (size_t i = 0; i < points.size(); i++) {
		glVertex2d(points[i].getX(), points[i].getY());	
	}

	glEnd();	
}

//Display Event
void display(void) {
	Main *main = Main::getInstance();
	vector<Curve*> curves = main->getCurves();

	glClear(GL_COLOR_BUFFER_BIT);				
	
	for (size_t i = 0; i < curves.size(); i++) {
		if (main->getSelectedCurve() == i)
			curves.at(i)->draw(COLOR_RED);
		else
			curves.at(i)->draw(COLOR_GREEN);
	}

	drawControlPoints();
	
	glutSwapBuffers();
}

//Keyboard Event
void keyboard(unsigned char key, int x, int y) {
	Main *main = Main::getInstance();
	if (key == GLUT_KEY_ENTER && main->getState() == CREATING_BSPLINE) {
		main->refreshCurrentCurve();

		if (main->getCurrentCurve()->hasAllControlPoints()) {
			main->addCurve(main->getCurrentCurve());
			Main::getInstance()->setState(NO_STATE);
			
		}
	}
	glutPostRedisplay();
}

//Menu Event
void menu(int option) {
	Main *main = Main::getInstance();

	switch(option) {
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
		case 2:
			main->setAssignedType((CURVE_TYPE)option);
			if (main->getState() == NO_STATE)
				main->setState(TYPE_ASSIGNED);
			else if (main->getState() == DEGREE_ASSIGNED)
				main->setState(TYPE_AND_DEGREE_ASSIGNED);
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			main->setAssignedDegree(option);
			if (main->getState() == TYPE_ASSIGNED)
				main->setState(TYPE_AND_DEGREE_ASSIGNED);
			else if (main->getState() == NO_STATE)
				main->setState(DEGREE_ASSIGNED);
			//Por enquanto essa condição está travando o programa porque não chegamos ainda a tratar esse estado! Descomentar quando for ser tratado!
			//else if (main->getState() == CURVE_SELECTED)
			//	main->setState(EDITING_CONTROL_POINTS;
			break;

		case 11:
			if (main->getState() == TYPE_AND_DEGREE_ASSIGNED) {
				if (main->getAssignedType() == BEZIER) {
					main->setCurrentCurve(new BezierCurve());
					main->setState(CREATING_BEZIER_CURVE);
				}
				else if (main->getAssignedType() == BSPLINE) {
					main->setCurrentCurve(new BSpline());
					main->setState(CREATING_BSPLINE);
				}
                
				main->setCurrentCurveDegree(main->getAssignedDegree());
			}
			break;

		case 12: {
			string filename;
			cout << "Digite o nome do arquivo onde deseja salvar as curvas: ";
			cin >> filename;
			saveCurves(filename) ? cout << "As curvas foram salvas com sucesso!" << endl : cout << "Houve um erro no salvamento das curvas." << endl;
			break;
		}

		case 13: {
			string filename;
			cout << "Digite o nome do arquivo de onde deseja carregar as curvas: ";
			cin >> filename;
			loadCurves(filename) ? cout << "As curvas foram carregadas com sucesso!" << endl : cout << "Houve um erro no carregamento das curvas." << endl;;
			break;
		}

		case 14:
			if (main->getState() == CURVE_SELECTED) {
				main->setState(TRANSLATING_CURVE);
			}
			break;

		case 15:
			if (main->getState() == CURVE_SELECTED) {
				main->setState(ROTATING_CURVE);
			}
			break;

		case 16:
			if (main->getState() == CURVE_SELECTED) {
				main->setState(SCALING_CURVE);
			}
			break;

		case 17:
			if (main->getState() == CURVE_SELECTED) {
				vector<Curve*> curves = main->getCurves();
				curves.erase(curves.begin() + main->getSelectedCurve());
				main->setCurves(curves);
				main->setState(NO_STATE);
				main->setCurrentCurve(new Curve());
			}
			break;
	}

	glutPostRedisplay();
}
