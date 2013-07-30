#include "eventhandler.h"
#include "filehandler.h"
#include "beziercurve.h"
#include "bspline.h"
#include "main.h"

#include <iostream>

Point mouseLastPosition;

//Control Point Selection
int checkControlPointHit(int x, int y) {
	vector<Point> points = Main::getInstance()->getCurrentCurve()->getControlPoints();

	for (size_t i = 0; i < points.size(); i++) {
		if ( (x > (points.at(i).getX() - POINT_ACCURACY_SIZE) && x < (points.at(i).getX() + POINT_ACCURACY_SIZE)) && 
			(y > (points.at(i).getY() - POINT_ACCURACY_SIZE) && y < (points.at(i).getY() + POINT_ACCURACY_SIZE)) )
			return i;
	}
	return -1;
}

//Curve Selection
int checkCurveHit(int x, int y) {
	vector<Curve*> curves = Main::getInstance()->getCurves();

	for (size_t i = 0; i < curves.size(); i++) {
		vector<Point> points = curves.at(i)->getCurvePoints();

		for (size_t j = 0; j < points.size(); j++) {
			//Declarei constantes só para facilitar a leitura (evandromendonca)
			if ( (x > (points.at(j).getX() - CURVE_ACCURACY_SIZE) && x < (points.at(j).getX() + CURVE_ACCURACY_SIZE)) && 
				(y > (points.at(j).getY() - CURVE_ACCURACY_SIZE) && y < (points.at(j).getY() + CURVE_ACCURACY_SIZE)) )
				return i;
		}
	}
	return -1;
}

//Mouse Event
void mouse(int button, int state, int x, int y) {
	Main *main = Main::getInstance();

	//Get mouse down position
	if ( button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN )
		mouseLastPosition.setPosition((double)x, (double)y);

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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && 
		(main->getState() == NO_STATE || main->getState() == CURVE_SELECTED ||
		 main->getState() == TRANSLATING_CURVE || main->getState() == ROTATING_CURVE_SCREEN ||
		 main->getState() == SCALING_CURVE)) {
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

	//Stop the motion of the control point
	if (main->getState() == MOVING_CONTROL_POINTS) {
		main->setState(CURVE_SELECTED);
	}

	//Other cases
	glutPostRedisplay();
}

//Mouse Motion Event
void mouseMotion(int x, int y) {

	//Generating mouse move distance
	Point mouseMoveDistance = Point(x - mouseLastPosition.getX(), y - mouseLastPosition.getY());

	Main *main = Main::getInstance();

	//Moving Control Points
	if (main->getState() == CURVE_SELECTED) {
		main->setSelectedPoint(checkControlPointHit(x, y));

		if (main->getSelectedPoint() != -1) 
			main->setState(MOVING_CONTROL_POINTS);
	}
	else if (main->getState() == MOVING_CONTROL_POINTS) {
		main->getCurrentCurve()->moveControlPoint(x, y, main->getSelectedPoint());
	}

	//Translating Curve
	if (main->getState() == TRANSLATING_CURVE) {
		main->getCurrentCurve()->translateCurve(mouseMoveDistance);
	}

	//Rotating Curve
	if (main->getState() == ROTATING_CURVE_SCREEN) {
		main->getCurrentCurve()->rotateCurveScreen(mouseMoveDistance);		
	}

	//Scaling Curve
	if (main->getState() == SCALING_CURVE) {
		main->getCurrentCurve()->scaleCurve(mouseMoveDistance);
	}

	//Set MouseLastPosition
	mouseLastPosition.setPosition(x, y);

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

void drawReferencialLines() {
	glColor3f(COLOR_WHITE);
	glBegin(GL_LINES);
	
	// Ver como pegar por variaveis o tamanho da janela para fazer essa contas
	glVertex2f(CENTER_X, 0);
	glVertex2f(CENTER_X, CENTER_Y*2);
	glVertex2f(0, CENTER_Y);
	glVertex2f(CENTER_X*2, CENTER_Y);
	glEnd();
}

//Display Event
void display(void) {
	Main *main = Main::getInstance();
	vector<Curve*> curves = main->getCurves();

	glClear(GL_COLOR_BUFFER_BIT);

	if (main->getState() == ROTATING_CURVE_SCREEN)
		drawReferencialLines();

	for (size_t i = 0; i < curves.size(); i++) {
		if (main->getSelectedCurve() == i)
			curves.at(i)->draw(COLOR_RED);
		else
			curves.at(i)->draw(COLOR_GREEN);
	}

	drawControlPoints();

	glutSwapBuffers();
}

void reshape(int width, int height) {
	if( width != GL_WINDOW_WIDTH || height != GL_WINDOW_HEIGHT ) { 
		glutReshapeWindow( GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT); 
	}
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

	if (key == GLUT_KEY_ENTER && main->getState() == CURVE_SELECTED) {
		main->setSelectedCurve(-1);
		main->setCurrentCurve(new Curve());
		main->setState(NO_STATE);
		main->createMenu();
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
		//else if (main->getState() == CURVE_SELECTED) {
		//	main->setState(EDITING_CONTROL_POINTS);
		//	main->setCurrentCurveDegree(option);
		//}
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
		if (main->getState() == CURVE_SELECTED)
			main->setState(TRANSLATING_CURVE);
		break;

	case 15:
		if (main->getState() == CURVE_SELECTED)
			main->setState(ROTATING_CURVE_SCREEN);
		break;

	case 16:
		if (main->getState() == CURVE_SELECTED)
			main->setState(ROTATING_CURVE_AXIS);
		break;

	case 17:
		if (main->getState() == CURVE_SELECTED)
			main->setState(SCALING_CURVE);
		break;

	case 18:
		if (main->getState() == CURVE_SELECTED) 
			main->deleteCurve();
		break;
	}

	glutPostRedisplay();
}
