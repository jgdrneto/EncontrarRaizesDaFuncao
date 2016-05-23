//Incluindo biblioteca necessárias
#include <locale.h>
#include <string.h>

#include "algoritmo.cpp"

/**
* Descrição: Limpa o console
*/
void limpaTela(){
	if(system("clear")){
		system("cls");
	}
}

/*
* Descrição: Aplica o algorimo escolhido pelo usuário 
* @params int : número do algoritmo de refinamento  que se deseja executar
* @params int : número do algoritmo de isolamento que se deseja executar
* @params Polinomio& : Polinômio em que se deseja aplicar o algoritmo	
*/
void aplicarAlgorimo(int escolhaRefinamento, int escolhaIsolamento, Polinomio& polinomio){
	//Intervalo que será obtido no isolamento
	Intervalo intervalo; 

	//Aplicando o método de isolamento escolhido pelo usuário
	switch(escolhaIsolamento){
		case 1:
			//variável para escolher o x inicial
			int xInicial;

			//Pedindo o x inicial ao usuário
			cout << "Escolha o x inicial para o método de isolamento de troca de sinal: ";
			cin >> xInicial;

			intervalo = Algoritmo::metodoTrocaDeSinal(polinomio, xInicial);
			
			cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;
		break;
		case 2:
			intervalo = Algoritmo::metodoDeLagrange(polinomio);

			cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;
		break;
	}

	//Variável que guardará a aproximação feita por um dos métodos
	long double aproximacao=0;

	//Aplicando o método de refinamento escolhido pelo usuário
	switch(escolhaRefinamento){
		case 1:
			cout << "Resultado usando método de bisserção: ";
			aproximacao = Algoritmo::metodoDaBissercao(polinomio, intervalo);
			cout << aproximacao << endl;
		break;
		case 2:
			cout << "Resultado usando método das cordas: "; 
			aproximacao = Algoritmo::metodoDasCordas(polinomio, intervalo);
			cout << aproximacao << endl;
		break;
		case 3:
			cout << "Resultado usando método do ponto fixo: "; 
			aproximacao = Algoritmo::metodoDoPontoFixo(polinomio, intervalo);
			cout << aproximacao << endl;
		break;
		case 4:
			cout << "Resultado usando método de Newton: "; 
			aproximacao = Algoritmo::metodoDeNewton(polinomio, intervalo);
			cout << aproximacao << endl;
		break;
	}

	printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(aproximacao));
}

/**
* Descrição: Escreve o menu de escolha dos algoritmos no terminal
* @return : Inteiro representando a escolha do usuário
*/
int menuInicial(){	
	//Inicializando variáveis
	int escolha = 0;	
	//Menu para escolha do métodode isolamento que se deseja utilizar
	do {
		cout << "Deseja resolver encontrar raíze(s) de uma equação ou um sistema de equações:" << endl;
		cout << "1 - Uma equação" <<endl;
		cout << "2 - Sistema de equações" << endl;
		cout << "-> ";
		cin >> escolha;
	}while(escolha <1 || escolha >2);

	//Limpa a tela do console
	limpaTela();

	//Retorna o valor da escolha
	return escolha;
}

/**
* Descrição: Escreve o menu de escolha dos algoritmos no terminal
* @return : Inteiro representando a escolha do usuário
*/
int menuIsolamento(){
	
	//Inicializando variáveis
	int escolha = 0;	
	//Menu para escolha do métodode isolamento que se deseja utilizar
	do {
		cout << "Qual método de isolamento deseja usar: " << endl;
		cout << "1 - Método de troca de sinais" <<endl;
		cout << "2 - Método de Lagrange" << endl;
		cout << "-> ";
		cin >> escolha;
	}while(escolha <1 || escolha >2);

	//Limpa a tela do console
	limpaTela();

	//Retorna o valor da escolha
	return escolha;
}

/**
* Descrição: Escreve o menu de escolha dos algoritmos no terminal
* @return : Inteiro representando a escolha do usuário
*/

int menuRefinamento(){
	
	//Inicializando variáveis
	int escolha = 0;	
	//Menu para escolha do métodode refinamento que se deseja utilizar
	do {
		cout << "Qual método de refinamento deseja usar: " << endl;
		cout << "1 - Método de bisserção" <<endl;
		cout << "2 - Método das cordas" << endl;
		cout << "3 - Método do ponto fixo" << endl;
		cout << "4 - Método de Newton" << endl;
		cout << "-> ";
		cin >> escolha;
	}while(escolha <1 || escolha >4);

	//Limpa a tela do console
	limpaTela();

	//Retorna o valor da escolha
	return escolha;
}

/**
* Descrição: Verifica se a versão usada será a de testes
* @params int : Quantidade de argumentos no comando de compilação
* @params char* : Vetor com os argumentos do comando de compilação
* @return : Verdadeiro se existe o programa com o nome TESTE e falso caso contrário
*/

bool teste(int argc,char* argv[]){
	for(int i=0;i<argc;i++){
		if(strcmp(argv[i], "TESTE")==0){
			return true;
		}
	}
	return false;
}	

void preencherValores(Polinomio* polinomios){
	//Adicionando valores estáticos ao polinômios

	//-----------------------------------------------------------

	//Polinomio 1 | x² -2 |
	
	//Criando polinômios
	polinomios[0] = *(new Polinomio(2));

	//Adicionando valores
	polinomios[0].getPolinomio()[0] = -2; 
	polinomios[0].getPolinomio()[1] = 0;
	polinomios[0].getPolinomio()[2] = 1;
	
	//-----------------------------------------------------------

	//Polinomio 2 | x³ - x² - 1 |
	
	//Criando polinômios
	polinomios[1] = *(new Polinomio(3));

	//Adicionando valores
	polinomios[1].getPolinomio()[0] = -1; 
	polinomios[1].getPolinomio()[1] = 0;
	polinomios[1].getPolinomio()[2] = -1;
	polinomios[1].getPolinomio()[3] = 1;

	//-----------------------------------------------------------
	//Polinomio 3 | x⁴ - 2x³ + x² -3x - 1 |

	//Criando polinômios
	polinomios[2] = *(new Polinomio(4));

	//Adicionando valores
	polinomios[2].getPolinomio()[0] = -1; 
	polinomios[2].getPolinomio()[1] = -3;
	polinomios[2].getPolinomio()[2] = 1;
	polinomios[2].getPolinomio()[3] = -2;
	polinomios[2].getPolinomio()[4] = 1;

	//-----------------------------------------------------------

}

void preencherValores(MatrizPolinomioComposto& F1, MatrizPolinomioComposto& F2){
	// ay^2 + by + c
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[0] = -1; // c = -1
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[1] = 0; // b = 0
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[2] = 1; // a = 1
	// y^2 - 1

	// ax^2 + by + c
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[0] = 0; // c = 0
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[1] = 0; // b = 0
	F1.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[2] = 1; // a = 1
	// x^2

	// ay + c
	F1.getMatrizPolinomioComposto()[1].getPolinomioComposto()[0].getPolinomio()[0] = -1; // c = -1
	F1.getMatrizPolinomioComposto()[1].getPolinomioComposto()[0].getPolinomio()[1] = 1; // a = 1
	// y - 1

	// ax + c
	F1.getMatrizPolinomioComposto()[1].getPolinomioComposto()[1].getPolinomio()[0] = 0; // c = 0
	F1.getMatrizPolinomioComposto()[1].getPolinomioComposto()[1].getPolinomio()[1] = 1; // a = 1
	// x



	// ay^2 + by + c
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[0] = -2; // c = -2
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[1] = 0; // b = 0
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[0].getPolinomio()[2] = 1; // a = 1
	// y^2 + y - 1

	// ax^2 + by + c
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[0] = -2; // c = -2
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[1] = 0; // b = 0
	F2.getMatrizPolinomioComposto()[0].getPolinomioComposto()[1].getPolinomio()[2] = 1; // a = 1
	// x^2 + x

	// ay + c
	F2.getMatrizPolinomioComposto()[1].getPolinomioComposto()[0].getPolinomio()[0] = -1; // c = -1
	F2.getMatrizPolinomioComposto()[1].getPolinomioComposto()[0].getPolinomio()[1] = 1; // a = 1
	// y - 1

	// ax + c
	F2.getMatrizPolinomioComposto()[1].getPolinomioComposto()[1].getPolinomio()[0] = -1; // c = -1
	F2.getMatrizPolinomioComposto()[1].getPolinomioComposto()[1].getPolinomio()[1] = 1; // a = 1
	// x
}

void preencherValores(Matriz& m){
	m.adicionarValores(2, 0, 0);
	m.adicionarValores(1, 1, 0);
}

//Método principal do programa
int main(int argc, char*argv[]){

	//Aumentando precisão do cout	
	std::cout.precision(15);

	//Inicializando variáveis	
	int n = -1;
	
	//Permitindo caracteres especiais
	setlocale(LC_ALL, "Portuguese");
	
	//Verifica se foi solicitado o teste ou não
	if(!teste(argc,argv)){	

		//Decide se vai ser método de quase-Newton ou não
		int i = menuInicial();

		//Uma equação
		if(i==1){
			do{
				//Estrutura de repetição para decidir o grau do polinômio
				cout << "Digite o grau do polinômio: ";
				cin >> n;
			}while(n == -1);

			//Cria o polinômio
			Polinomio polinomio(n);

			//Adiciona os valores númericos na matriz
			polinomio.adicionarValores();

			cout << "Polinômio: ";
			polinomio.imprimir();

		 	//Aplicando os algoritmos
			aplicarAlgorimo(menuRefinamento(),menuIsolamento(), polinomio);
		}else{

			//Sistema de equações
			do{
				cout << "Digite a quantidade de variáveis do seu sistema: " << endl;
				cin >> n;
			}while(n==-1);

			Matriz graus(n,1);
			cout << "Digite os graus de cada equação, um por vez:" << endl;
			graus.adicionarValores();

			MatrizPolinomioComposto Func(n,graus);
			for(int i = 0; i < Func.getQtdPc(); i++){
				for(int j = 0; j < n; j++){
					Func.getMatrizPolinomioComposto()[i].getPolinomioComposto()[j].adicionarValores();
				}
			}
			Func.imprimir();

			Matriz xInicial(n,1);
			cout << "Digite os valores iniciais das variáveis, na ordem de criação:" << endl;
			xInicial.adicionarValores();

			Matriz aproximacao(n,1);
			aproximacao = Algoritmo::metodoQuaseNewton(Func, xInicial);

			cout << "Aproximação: " << endl;
			for(int i = 0; i < n; i++){
				printf("| %.15f |\n", aproximacao.getValor(i,0));
			}

			cout << "Resultado aplicado no polinomio:" << endl;
			for(int i = 0; i < n; i++){
				printf("| %.15f |\n", Func.getResultado(aproximacao).getValor(i,0));
			}
		}
	}else{
		
		//Área reservada a testes

		Polinomio polinomio(2);
		Matriz graus1(2,1);
		Matriz graus2(2,1);

		preencherValores(graus1);
		preencherValores(graus2);

		MatrizPolinomioComposto F1(2, graus1);
		MatrizPolinomioComposto F2(2, graus2);

		//Adicionando valores estáticos a matriz
		preencherValores(F1, F2);

		Matriz x(2, 1);
		x.adicionarValores(0, 0, 0);
		x.adicionarValores(0, 1, 0);

		Intervalo intervalo;

		Polinomio polinomios[3];

		preencherValores(polinomios);

		for(int i=0;i<3;i++){

			cout << "=================================\n" << endl;

			cout << "Polinômio: " << endl;
			polinomios[i].imprimir();

			cout << "\n=================================\n" << endl;
				
			//Verificando soluções por TROCA DE SINAL

			cout << "Usando Método de refinamento por troca de sinal: " << endl;
			
			intervalo = Algoritmo::metodoTrocaDeSinal(polinomios[i], 0);

			cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;

			cout << "----------------------------------------------------" << endl;

			//Método da bisserção usando troca de sinal

			cout << "Usando Método de bisserção usando Troca de sinal: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDaBissercao(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDaBissercao(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDaBissercao(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			//método das cordas

			cout << "Usando Método das cordas usando troca de sinal: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDasCordas(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDasCordas(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			cout << "Usando Método do ponto fixo usando troca de sinal: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			cout << "Usando Método de Newton usando troca de sinal: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDeNewton(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDeNewton(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDeNewton(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}
			
			cout << "----------------------------------------------------" << endl;

			//Verificando soluções por LAGRANGE

			cout << "Usando Método de refinamento por Lagrange: " << endl;
				
			intervalo = Algoritmo::metodoDeLagrange(polinomios[i]);

			cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;

			cout << "----------------------------------------------------" << endl;

			//método da bisserção usando Lagrange

			cout << "Usando Método de bisserção usando Lagrange: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDaBissercao(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDaBissercao(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDaBissercao(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			//métpolinomios[i]odo das cordas

			cout << "Usando Método das cordas usando Lagrange: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDasCordas(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDasCordas(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			cout << "Usando Método do ponto fixo usando Lagrange: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDoPontoFixo(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;

			cout << "Usando Método de Newton usando Lagrange: " << endl;

			cout << "Valor da aproximação é: " << Algoritmo::metodoDeNewton(polinomios[i], intervalo) << endl;

			printf("Resultado aplicado no polinomio: %.15Lf \n", polinomios[i].getResultado(Algoritmo::metodoDeNewton(polinomios[i], intervalo)));

			if(abs(polinomios[i].getResultado(Algoritmo::metodoDeNewton(polinomios[i], intervalo))) <=ERRO){
				cout << "CORRETO" << endl;
			}else{
				cout << "ERRADO" << endl;
			}

			cout << "----------------------------------------------------" << endl;
		
		}

		cout << "Sistemas não-lineares" << endl;
			
		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método quase-Newton: " << endl;

		cout << "F(x) = |x^2 + y^2 - 1 |" << endl;
		cout << "       |x + y - 1     |" << endl;

		Matriz xap = Algoritmo::metodoQuaseNewton(F1, x);

		cout << "Valor da aproximação é: [ " << xap.getValor(0,0) << " , " << xap.getValor(1,0) << "]" << endl;

		printf("Resultado aplicado no polinomio:[ %.15f  %.15f ]\n", F1.getResultado(xap).getValor(0,0), F1.getResultado(xap).getValor(1,0));

		if(F1.getResultado(xap).norma() <= ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}
			
		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método quase-Newton: " << endl;

		cout << "F(x) = |x^2 + y^2 + x + y - 2 |" << endl;
		cout << "       |x + y - 1     |" << endl;

		xap = Algoritmo::metodoQuaseNewton(F2, x);

		cout << "Valor da aproximação é: [ " << xap.getValor(0,0) << " , " << xap.getValor(1,0) << "]" << endl;

		printf("Resultado aplicado no polinomio:[ %.15f  %.15f ]\n", F2.getResultado(xap).getValor(0,0), F2.getResultado(xap).getValor(1,0));
		if(F2.getResultado(xap).norma() <= ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}
		
		cout << "----------------------------------------------------" << endl;
	}	
	return 0;
}