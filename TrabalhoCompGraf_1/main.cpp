#include "main.h"

int getValue(string str) { 
	int value;

	stringstream strStream(str.c_str());
	strStream >> value;

	return value;
}

void saveCurves(string fileName) {
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
	else
		cout << "Couldn't open file";

	output.close();
}

void loadCurves(string fileName) {
	ifstream input;
	input.open(fileName, ios::in);
	
	if(input.is_open()) {
		Curve *curve;
		Point point;
		string buffer = "";	

		while(!input.eof()) { 
			input >> buffer;

			if (buffer == "BEGIN_CURVE") {
				if (currentState == WAITING_BEGIN)
					curves.push_back(curve);
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
		currentState = NO_STATE;
		input.close();
	}
	else
		cout << "Couldn't open file";
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
			else if (currentState == CURVE_SELECTED)
				currentState = EDITING_CONTROL_POINTS;
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
			cout << "Digite o nome do arquivo onde deseja salvar as curvas:" << endl;
			cin >> filename;
			saveCurves(filename);
			break;
		}

		case 13: {
			string filename;
			cout << "Digite o nome do arquivo de onde deseja carregar as curvas:" << endl;
			cin >> filename;
			loadCurves(filename);
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
			}
			break;
	}

	glutPostRedisplay();
}

void createMenu(void) {
	curveTypeSubMenuID = glutCreateMenu(menu);
	glutAddMenuEntry("Bézier", 1);
	glutAddMenuEntry("B-Spline", 2);

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

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle() {
    glutSetWindow(window);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	//Criando Pontos de controle iniciais da curva
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentState == CREATING_CURVE)
		currentCurve->addControlPoint(x, y);
	if (currentState == CREATING_CURVE && currentCurve->hasAllControlPoints()) {
		curves.push_back(currentCurve);
		currentState = NO_STATE;
	}

	//Outros casos:

    
    glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);


	
	vector<Point> points = currentCurve->getControlPoints();
	for(size_t i = 0; i < points.size(); i++) {
		glVertex2f(points.at(i).getX(), points.at(i).getY());
	}


	for (size_t i = 0; i < curves.size(); i++) {
		points = curves.at(i)->getControlPoints();

		for (size_t j = 0; j < points.size(); j++) {
			glVertex2f(points.at(j).getX(), points.at(j).getY());
		}
	}

	glEnd();

	glutSwapBuffers();
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);  
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
