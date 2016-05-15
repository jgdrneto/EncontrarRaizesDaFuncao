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

void preencherValores(Polinomio& polinomio){
	//Adicionando valores estáticos a matriz
	polinomio.getPolinomio()[0] = -2; 
	polinomio.getPolinomio()[1] = 0;
	polinomio.getPolinomio()[2] = 1;
	//polinomio.getPolinomio()[3] = 1;
	//polinomio.getPolinomio()[4] = 1;    
	
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
				cout << "Digite a quantidade de variáveis do seu sistema" << endl;
				cin >> n;
			}while(n==-1);


		}
	}else{
		
		//Área reservada a testes

		Polinomio polinomio(2);	

		//Adicionando valores estáticos a matriz
		preencherValores(polinomio);

		cout << "Polinômio: " << endl;
		polinomio.imprimir();

		Intervalo intervalo;

		//Verificando soluções por TROCA DE SINAL

		cout << "Usando Método de refinamento por troca de sinal: " << endl;
		
		intervalo = Algoritmo::metodoTrocaDeSinal(polinomio, 0);

		cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;

		cout << "----------------------------------------------------" << endl;

		//Método da bisserção usando troca de sinal

		cout << "Usando Método de bisserção usando Troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDaBissercao(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDaBissercao(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDaBissercao(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		//método das cordas

		cout << "Usando Método das cordas usando troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDasCordas(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDasCordas(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método do ponto fixo usando troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDoPontoFixo(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDoPontoFixo(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDoPontoFixo(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método de Newton usando troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDeNewton(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDeNewton(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDeNewton(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}
		
		cout << "----------------------------------------------------" << endl;

		//Verificando soluções por LAGRANGE

		cout << "Usando Método de refinamento por Lagrange: " << endl;
			
		intervalo = Algoritmo::metodoDeLagrange(polinomio);

		cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;

		cout << "----------------------------------------------------" << endl;

		//método da bisserção usando Lagrange

		cout << "Usando Método de bisserção usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDaBissercao(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDaBissercao(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDaBissercao(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		//método das cordas

		cout << "Usando Método das cordas usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDasCordas(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDasCordas(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método do ponto fixo usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDoPontoFixo(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDoPontoFixo(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDoPontoFixo(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

		cout << "Usando Método de Newton usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDeNewton(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoDeNewton(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoDeNewton(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;
		
		cout << "Sistemas não-lineares" << endl;
		
		cout << "----------------------------------------------------" << endl;

		/*Essa parte é bastante diferente das outras, é preciso criar uma matriz coluna de soluções e
		  usar uma matriz de polinômios compostos (para ser a F(x)). Uma maneira de fazer isso é usar herança para uma nova classe	
		  chamanda polinomio composto, e nela estiver uma lista de polinomios simples, um polinomio para cada variável
		  
		  Obs: É importante usar uma nova classe para usar como polinomio composto, já que em um mesmo 
		  polinomio composto poderemos ter P(x,y)= x^2 + y^4 + y^3 + x + 1. O q dificulta muito somente a classe
		  feita aqui ainda  

		  Pode-se deixar a classe matriz totalmente template, e usá-la no lugar da lista que estará 
		  em polinômios compostos.	
		  	
		*/
		cout << "Usando Método quase-Newton: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoQuaseNewton() << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoQuaseNewton()));

		if(abs(polinomio.getResultado(Algoritmo::metodoQuaseNewton())) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;		
	}

	return 0;
}