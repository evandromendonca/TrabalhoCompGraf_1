#include "curvas.h"

//Funcao para verificar se o valor digitado pelo usuario é valido
int verificaEntrada(int min, int max) {
	int opcaoEscolhida = -1;

	cin >> opcaoEscolhida;

	while( opcaoEscolhida < min || opcaoEscolhida > max ) {
		cout << "Opcao invalida." << endl << "Digite o numero da opcao desejada" << endl;

		cin >> opcaoEscolhida;	
	}

	return opcaoEscolhida;
}

void desenhaSubMenuTipoDeCurva() {
	int opcaoEscolhida = -1;

	//escrevendo as opcoes do submenu de tipos de curva
	cout << "1 - Curva de Bezier" << endl;
	cout << "2 - B-Spline" << endl;

	opcaoEscolhida = verificaEntrada(1, 2);
}

void desenhaMenu() {
	int opcaoEscolhida = -1;

	cout << "Escolha a opcao desejada:" << endl << endl;

	//Escrevendo as opcoes do menu principal
	cout << "1 - Escolher tipo de curva" << endl;
	cout << "2 - Escolher grau da curva" << endl;
	cout << "3 - Criar curva" << endl;
	cout << "4 - Excluir curva" << endl;
	cout << "5 - Salvar curva" << endl;
	cout << "6 - Carregar curva" << endl;

	opcaoEscolhida = verificaEntrada(1, 6);

	//Verifica qual foi a opcao selecionada, para executar a acao escolhida
	switch(opcaoEscolhida) {
		case 1:
			system("CLS");
			desenhaSubMenuTipoDeCurva();
			break;

		case 2:
			system("CLS");
			break;

		case 3:
			system("CLS");
			break;

		case 4:
			system("CLS");
			break;

		case 5:
			system("CLS");
			break;

		case 6:
			system("CLS");
			break;
	}
}




