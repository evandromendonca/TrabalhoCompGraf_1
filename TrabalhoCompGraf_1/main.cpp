#include "main.h"

int getValue(string str) { 
	int value;

	stringstream strStream(str.c_str());
	strStream >> value;

	return value;
}

bool saveCurves(string fileName) {
	ofstream output;
	output.open(fileName, ios::trunc);
	
	if(output.is_open()) {
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
	}
	else {
		cout << "Couldn't open file";
		output.close();
		return false;
	}

	output.close();
	return true;
}

bool loadCurves(string fileName) {
	ifstream input;
	input.open(fileName, ios::in);
	
	if(input.is_open()) {
		Curve *curve;
		Point point;
		string buffer = "";	

		while(!input.eof()) { 
			input >> buffer;

			if (buffer == "BEGIN_CURVE") {
				if (currentState == WAITING_BEGIN) {
					curve->refresh();
					curves.push_back(curve);
				}
				currentState = READING_TYPE;
			}
			else if (currentState == READING_TYPE) {
				if (buffer == "1")	
					curve = new BezierCurve();
				else
					curve = new BSpline();

				currentState = READING_DEGREE;
			}
			else if (currentState == READING_DEGREE) {
				curve->setCurveDegree(getValue(buffer));

				currentState = READING_POINTS;
			}
			else if (currentState == READING_POINTS) {
				if (buffer == "END_CURVE")
					currentState = WAITING_BEGIN;
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
		currentState = NO_STATE;
		input.close();
		return true;
	}
	else {
		cout << "Couldn't open file";
		return false;
	}
}

void menu(int option) {
	switch(option) {
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
		case 2:
			typeAssigned = (CURVE_TYPE)option;
			if (currentState == NO_STATE)
				currentState = TYPE_ASSIGNED;
			else if (currentState == DEGREE_ASSIGNED)
				currentState = TYPE_AND_DEGREE_ASSIGNED;
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			degreeAssigned = option;
			if (currentState == TYPE_ASSIGNED)
				currentState = TYPE_AND_DEGREE_ASSIGNED;
			else if (currentState == NO_STATE)
				currentState = DEGREE_ASSIGNED;
			//Por enquanto essa condição está travando o programa porque não chegamos ainda a tratar esse estado! Descomentar quando for ser tratado!
			//else if (currentState == CURVE_SELECTED)
			//	currentState = EDITING_CONTROL_POINTS;
			break;

		case 11:
			if (currentState == TYPE_AND_DEGREE_ASSIGNED) {
				if (typeAssigned == BEZIER)
					currentCurve = new BezierCurve();
				else if (typeAssigned == BSPLINE)
					currentCurve = new BSpline();
				else
					currentCurve = new Curve();
                
				currentCurve->setCurveDegree(degreeAssigned);
				currentState = CREATING_CURVE;
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
			if (currentState == CURVE_SELECTED) {
				currentState = TRANSLATING_CURVE;
			}
			break;

		case 15:
			if (currentState == CURVE_SELECTED) {
				currentState = ROTATING_CURVE;
			}
			break;

		case 16:
			if (currentState == CURVE_SELECTED) {
				currentState = SCALING_CURVE;
			}
			break;

		case 17:
			if (currentState == CURVE_SELECTED) {
				curves.erase(curves.begin() + selectedCurveIndex);
				currentState = NO_STATE;
				currentCurve = new Curve();
			}
			break;
	}

	glutPostRedisplay();
}

void createMenu(void) {
	if (currentState == CURVE_SELECTED) {
		curveOptionsSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Transladar curva", 14);
		glutAddMenuEntry("Rotacionar curva", 15);
		glutAddMenuEntry("Escalar curva", 16);
		glutAddMenuEntry("Excluir curva", 17);

		menuID = glutCreateMenu(menu);
		glutAddSubMenu("Opções de curva", curveOptionsSubMenuID);
		glutAddMenuEntry("Sair", 0);
	}
	else {
		curveTypeSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Bézier", 1);
		glutAddMenuEntry("B-Spline uniforme", 2);

		curveDegreeSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("3", 3);
		glutAddMenuEntry("4", 4);
		glutAddMenuEntry("5", 5);
		glutAddMenuEntry("6", 6);
		glutAddMenuEntry("7", 7);
		glutAddMenuEntry("8", 8);
		glutAddMenuEntry("9", 9);
		glutAddMenuEntry("10", 10);

		curveOptionsSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Transladar curva", 14);
		glutAddMenuEntry("Rotacionar curva", 15);
		glutAddMenuEntry("Escalar curva", 16);
		glutAddMenuEntry("Excluir curva", 17);


		menuID = glutCreateMenu(menu);
		glutAddSubMenu("Escolher tipo de curva", curveTypeSubMenuID);
		glutAddSubMenu("Escolher grau da Curva", curveDegreeSubMenuID);
		glutAddMenuEntry("Criar curva", 11);
		glutAddMenuEntry("Salvar curvas", 12);
		glutAddMenuEntry("Carregar curvas", 13);
		glutAddSubMenu("Opções de curva", curveOptionsSubMenuID);
		glutAddMenuEntry("Sair", 0);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle() {
    glutSetWindow(window);
    glutPostRedisplay();
}

int checkCurveHit(int x, int y) {
	//Trocar a ordem, porque o ultimo supostamente foi desenhado por ultimo e tem preferencia na seleção por estar na "frente"
	for (size_t i = 0; i < curves.size(); i++) {
		vector<Point> points = curves.at(i)->getCurvePoints();

		for (size_t j = 0; j < points.size(); j++) {
			//Declarei constantes só para facilitar a leitura (evandromendonca)
			if ( (x > (points.at(j).getX() - ACCURACY_SIZE) && x < (points.at(j).getX() + ACCURACY_SIZE)) && (y > (points.at(j).getY() - ACCURACY_SIZE) && y < (points.at(j).getY() + ACCURACY_SIZE)))
				return i;
		}
	}
	return -1;
}

void mouse(int button, int state, int x, int y) {

	//Creating initial control points of the curve
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentState == CREATING_CURVE)
		currentCurve->addControlPoint(x, y);
	
	//Adding the curve to the list of curves if all the points are set and generating the curve points
	if (currentState == CREATING_CURVE && currentCurve->hasAllControlPoints()) {
		curves.push_back(currentCurve);
		currentCurve->refresh();
		currentState = NO_STATE;
	}

	//Checking selection of a curve
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (currentState == NO_STATE || currentState == CURVE_SELECTED)) {
		if ((selectedCurveIndex = checkCurveHit(x, y)) != -1) {
			currentCurve = curves.at(selectedCurveIndex);
			currentState = CURVE_SELECTED;
			createMenu();
		}
		else {
			currentCurve = new Curve();
			currentState = NO_STATE;
			createMenu();
		}
	}

	//Other cases


    glutPostRedisplay();
}

void drawControlPoints() {
	glColor3f(COLOR_BLUE);

	glBegin(GL_POINTS);

	//Draw only the control points of the current curve
	for (size_t i = 0; i < currentCurve->getControlPoints().size(); i++) {
		glVertex2d(currentCurve->getControlPoints()[i].getX(), currentCurve->getControlPoints()[i].getY());	
	}

	glEnd();	
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);				
	
	for (size_t i = 0; i < curves.size(); i++) {
		if (selectedCurveIndex == i)
			curves.at(i)->draw(COLOR_RED);
		else
			curves.at(i)->draw(COLOR_GREEN);
	}

	drawControlPoints();
	
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);  
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1024.0, 768.0, 0.0);
	glEnable( GL_POINT_SMOOTH );
    glEnable( GL_BLEND );
	glPointSize(5.0f);
}

int main(int argc, char **argv) {  
	//initialize program state and variables
	currentState = NO_STATE;
	currentCurve = new Curve();
	selectedCurveIndex = -1;
	typeAssigned = UNASSIGNED;


	//Initializing Glut
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);

	//Creating Glut window
	window = glutCreateWindow("Computação Gráfica - Trabalho 1");

	//Creating popup menu
    createMenu();

	//Initializing openGL environment
	init();

	//Setting function callbacks
    glutDisplayFunc(display);   
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	//Starting the Glut main loop
	glutMainLoop();

	//if everything runs correctly, exit with success code (0)
    exit(EXIT_SUCCESS);
}
