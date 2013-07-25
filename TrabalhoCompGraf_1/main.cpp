#include "main.h"
#include "eventhandler.h"

Main* Main::m_instance = NULL;
Curve* Main::m_pCurrentCurve = NULL;
STATE Main::m_currentState = NO_STATE;
int Main::m_selectedCurveIndex = -1;
int Main::m_menuID = -1;
int Main::m_curveTypeSubMenuID = -1;
int Main::m_curveDegreeSubMenuID = -1;
int Main::m_curveOptionsSubMenuID = -1;
int Main::m_degreeAssigned = -1;
CURVE_TYPE Main::m_typeAssigned = UNASSIGNED;

Main::Main() {

}

Main* Main::getInstance() {
	if (!m_instance)
		m_instance = new Main();

	return m_instance;
}

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

STATE Main::getState() {
	return m_currentState;
}

void Main::setState(STATE currentState) {
	m_currentState = currentState;
}

void Main::createMenu(void) {
	if (m_currentState == CURVE_SELECTED) {
		m_curveOptionsSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Transladar curva", 14);
		glutAddMenuEntry("Rotacionar curva", 15);
		glutAddMenuEntry("Escalar curva", 16);
		glutAddMenuEntry("Excluir curva", 17);

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

		m_curveOptionsSubMenuID = glutCreateMenu(menu);
		glutAddMenuEntry("Transladar curva", 14);
		glutAddMenuEntry("Rotacionar curva", 15);
		glutAddMenuEntry("Escalar curva", 16);
		glutAddMenuEntry("Excluir curva", 17);


		m_menuID = glutCreateMenu(menu);
		glutAddSubMenu("Escolher tipo de curva", m_curveTypeSubMenuID);
		glutAddSubMenu("Escolher grau da Curva", m_curveDegreeSubMenuID);
		glutAddMenuEntry("Criar curva", 11);
		glutAddMenuEntry("Salvar curvas", 12);
		glutAddMenuEntry("Carregar curvas", 13);
		glutAddSubMenu("Opções de curva", m_curveOptionsSubMenuID);
		glutAddMenuEntry("Sair", 0);
	}

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Main::run(int argc, char **argv) {
	//Initializing Main class members
	m_currentState = NO_STATE;
	m_pCurrentCurve = new Curve();
	m_selectedCurveIndex = -1;
	m_typeAssigned = UNASSIGNED;
	m_degreeAssigned = -1;

	//Initializing Glut
    glutInit(&argc, argv);

	//Preparing Glut environment
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768);

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
	glutDisplayFunc(display);  
	glutKeyboardFunc(keyboard);

	//Starting the Glut main loop
	glutMainLoop();
}

int main(int argc, char **argv) {
	//Start running the program
	Main::getInstance()->run(argc, argv);

	//if everything runs correctly, exit with success code (0)
    exit(EXIT_SUCCESS);
}
