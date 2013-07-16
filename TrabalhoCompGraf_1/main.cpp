#include "main.h"

void menu(int option) {
	switch(option) {
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
		case 2:
			currentCurve = new Curve();
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			currentCurve->setCurveDegree(option);
			break;

		case 11:
			if (currentCurve->getCurveDegree() >= 3 && currentCurve->getCurveDegree() <= 10 &&
				currentCurve->getControlPoints().size() < (size_t)(currentCurve->getCurveDegree() + 1))
				currentState = CREATING_CURVE;
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
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentState == CREATING_CURVE && currentCurve->getControlPoints().size() < (size_t)(currentCurve->getCurveDegree() + 1))
		currentCurve->addControlPoint(x,y);

	if (currentCurve->getControlPoints().size() == (currentCurve->getCurveDegree() + 1) && currentState == CREATING_CURVE) {
		curves.push_back(currentCurve);
		currentState = NO_STATE;
	}
	
    
    glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	for(size_t i = 0; i < currentCurve->getControlPoints().size(); i++) {
		Point p = currentCurve->getControlPoints().at(i);
		glVertex2f(p.getX(), p.getY());
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
	//initialize variables
	currentState = NO_STATE;
	currentCurve = new Curve();

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
