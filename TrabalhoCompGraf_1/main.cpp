#include "main.h"

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
            break;

		case 11:
			if (TYPE_AND_DEGREE_ASSIGNED) {
                if (typeAssigned == Bezier)
                    currentCurve = new BezierCurve();
                else
					currentCurve = new BSpline();
                
				currentCurve->setCurveDegree(degreeAssigned);
                currentState = CREATING_CURVE;
            }
			break;

		case 12:
			break;

		case 13:
			break;

		case 14:
			break;
	}

	glutPostRedisplay();
}

void createMenu(void) {     
	curveTypeSubMenuID = glutCreateMenu(menu);
    glutAddMenuEntry("B�zier", 1);
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

	menuID = glutCreateMenu(menu);
    glutAddSubMenu("Escolher tipo de curva", curveTypeSubMenuID);
    glutAddSubMenu("Escolher grau da Curva", curveDegreeSubMenuID);
	glutAddMenuEntry("Criar curva", 11);
	glutAddMenuEntry("Excluir curva", 12);
	glutAddMenuEntry("Salvar curvas", 13);
	glutAddMenuEntry("Carregar curvas", 14);
	glutAddMenuEntry("Sair", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle() {
    glutSetWindow(window);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentState == CREATING_CURVE)
		currentCurve->addControlPoint(x, y);

	if (currentState == CREATING_CURVE && currentCurve->getControlPoints().size() == (currentCurve->getCurveDegree() + 1)) {
		curves.push_back(currentCurve);
		currentState = NO_STATE;
	}
    
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

	//Initializing Glut
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);

	//Creating Glut window
	window = glutCreateWindow("Computa��o Gr�fica - Trabalho 1");

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
