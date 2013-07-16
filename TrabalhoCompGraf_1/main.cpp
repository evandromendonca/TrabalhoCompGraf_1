#include "main.h"

void menu(int option) {
	switch(option) {
		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
		case 2:
			currentCurve = new Curve();
			currentCurve->curveType = (CURVE_TYPE)option;
			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			currentCurve->curveDegree = option;
			break;

		case 11:
			if (currentCurve->curveDegree >= 3 && currentCurve->curveDegree <= 10 && currentCurve->curveType != NotSelected)
				drawingCurve = true;
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
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && drawingCurve && currentCurve->points.size() < (size_t)(currentCurve->curveDegree + 1))
		currentCurve->points.push_back(Point(x, y));

	if (currentCurve->points.size() == (currentCurve->curveDegree + 1) && drawingCurve) {
		curves.push_back(currentCurve);
		drawingCurve = false;
	}
	
    
    glutPostRedisplay();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glutSwapBuffers();
} 

int main(int argc, char **argv) {
	//initialize variables
	drawingCurve = false;
	currentCurve = new Curve();

	//Initializing Glut
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);

	//Creating Glut window
	window = glutCreateWindow("Computação Gráfica - Trabalho 1");

	//Creating popup menu
    createMenu();
	
	//Setting function callbacks
    glutDisplayFunc(display);   
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	//Starting the Glut main loop
	glutMainLoop();

	//if everything runs correctly, exit with success code (0)
    exit(EXIT_SUCCESS);
}
