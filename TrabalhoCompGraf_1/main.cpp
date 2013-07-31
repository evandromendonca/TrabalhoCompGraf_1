#include "main.h"
#include "eventhandler.h"

/* Construction */
Main* Main::m_instance = NULL;

Main::Main() {

}
/* Construction */


/* Singleton */
Main* Main::getInstance() {
	if (!m_instance)
		m_instance = new Main();

	return m_instance;
}
/* Singleton */


/* Curve Vector */
vector<Curve*> Main::getCurves() {
	return m_curves;
}

void Main::addCurve(Curve *curve) {
	m_curves.push_back(curve);
}

void Main::setCurves(vector<Curve*> curves) {
	m_curves.clear();
	
	for (size_t i = 0; i < curves.size(); i++) {
		m_curves.push_back(curves.at(i));
	}
}
/* Curve Vector */


/* Current State */
STATE Main::getState() {
	return m_currentState;
}

void Main::setState(STATE currentState) {
	m_currentState = currentState;
	createMenu();
}
/* Current State */


/* Current Curve */
Curve* Main::getCurrentCurve() {
	return m_pCurrentCurve;
}

void Main::setCurrentCurve(Curve *curve) {
	m_pCurrentCurve = curve;
}

void Main::addPointToCurrentCurve(Point point) {
	m_pCurrentCurve->addControlPoint(point);
}

void Main::addPointToCurrentCurve(double x, double y) {
	m_pCurrentCurve->addControlPoint(x, y);
}

void Main::setCurrentCurveDegree(int assignedDegree) {
	m_pCurrentCurve->setCurveDegree(assignedDegree);
}

void Main::refreshCurrentCurve() {
	m_pCurrentCurve->refresh();
}
/* Current Curve */


/* Selected Curve */
int Main::getSelectedCurve() {
	return m_selectedCurve;
}

void Main::setSelectedCurve(int selectedCurve) {
	m_selectedCurve = selectedCurve;
}
/* Selected Curve */

/* Selected Point */
int Main::getSelectedPoint() {
	return m_selectedPoint;
}

void Main::setSelectedPoint(int selectedPoint) {
	m_selectedPoint = selectedPoint;
}
/* Selected Curve */


/* Assigned Type */
CURVE_TYPE Main::getAssignedType() {
	return m_assignedType;
}

void Main::setAssignedType(CURVE_TYPE assignedType) {
	m_assignedType = assignedType;
}
/* Assigned Type */


/* Assigned Degree */
int Main::getAssignedDegree() {
	return m_assignedDegree;
}

void Main::setAssignedDegree(int assignedDegree) {
	m_assignedDegree = assignedDegree;
}
/* Assigned Degree */

void Main::deleteCurve() {
	m_curves.erase(m_curves.begin() + m_selectedCurve);
	setCurrentCurve(new Curve());
	setSelectedCurve(-1);
	setState(NO_STATE);
}


/* Menu */
void Main::createMenu(void) {
	if (m_currentState == CURVE_SELECTED) {
		m_rotateTypeSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Em torno ao centro da tela", 15);
		glutAddMenuEntry("Em torno do seu centro", 16);

		m_curveOptionsSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Transladar curva", 14);
		glutAddSubMenu("Rotacionar curva", m_rotateTypeSubMenuID);
		glutAddMenuEntry("Escalar curva", 17);
		glutAddMenuEntry("Excluir curva", 18);

		m_menuID = glutCreateMenu(menu);
		glutAddSubMenu("Opções de curva", m_curveOptionsSubMenuID);
		glutAddMenuEntry("Sair", 0);
	}
	else {
		m_curveTypeSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Bézier", 1);
		glutAddMenuEntry("B-Spline uniforme", 2);

		m_curveDegreeSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("3", 3);
		glutAddMenuEntry("4", 4);
		glutAddMenuEntry("5", 5);
		glutAddMenuEntry("6", 6);
		glutAddMenuEntry("7", 7);
		glutAddMenuEntry("8", 8);
		glutAddMenuEntry("9", 9);
		glutAddMenuEntry("10", 10);

		m_menuID = glutCreateMenu(menu);
		glutAddSubMenu("Escolher tipo de curva", m_curveTypeSubMenuID);
		glutAddSubMenu("Escolher grau da Curva", m_curveDegreeSubMenuID);
		glutAddMenuEntry("Criar curva", 11);
		glutAddMenuEntry("Salvar curvas", 12);
		glutAddMenuEntry("Carregar curvas", 13);
		glutAddMenuEntry("Sair", 0);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
/* Menu */


/* Run */
int Main::run(int argc, char **argv) {
	//Initializing Main class members
	m_currentState = NO_STATE;
	m_pCurrentCurve = new Curve();
	m_selectedCurve = -1;
	m_assignedDegree = -1;
	m_assignedType = UNASSIGNED;
	

	//Initializing Glut
    glutInit(&argc, argv);

	//Preparing Glut environment
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(GL_WINDOW_SIZE);

	//Creating Glut window
	m_window = glutCreateWindow("Computação Gráfica - Trabalho 1");

	//Creating menu
	createMenu();

	//Preparing OpenGL environment
	glClearColor(COLOR_BLACK, 0.0); 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(GL_SCREEN);
	glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
	glPointSize(5.0f);

	//Setting Glut function callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);  
	

	//Starting the Glut main loop
	glutMainLoop();

	return EXIT_SUCCESS;
}
/* Run */


/* Main */
int main(int argc, char **argv) {
	//Runs the program and exits at the end with success code if everything worked
    exit(Main::getInstance()->run(argc, argv));
}
/* Main */
