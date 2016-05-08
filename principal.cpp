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
* @params int : número do algoritmo de isolamento que se deseja executar
* @params int : número do algoritmo de refinamento que se deseja executar
* @params Polinomio& : Polinômio em que se deseja aplicar o algoritmo	
*/
void aplicarAlgorimo(int escolhaIsolamento,int escolhaRefinamento, Polinomio& polinomio){
	//Intervalo que será obtido no isolamento
	Intervalo intervalo; 

	//Aplicando o método de isolamento escolhido pelo usuário
	switch(escolhaIsolamento){
		case 1:
			//variável para escolher o x inicial
			int xInicial;

			//Pedindo o x inicial ao usuário
			cout << "Escolha o x inicial: ";
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
		case 5:
			cout << "Resultado usando método quase-Newton: "; 
			cout << Algoritmo::metodoDeNewton(polinomio, intervalo) << endl;
		break;
	}
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
		cout << "5 - Método quase-Newton" << endl;
		cout << "-> ";
		cin >> escolha;
	}while(escolha <1 || escolha >2);

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
		//Estrutura de repetição para decidir o grau do polinômio
		do{
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
		aplicarAlgorimo(menuIsolamento(),menuRefinamento(), polinomio);
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

		cout << "Usando Método quase-Newton usando troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoQuaseNewton(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoQuaseNewton(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoQuaseNewton(polinomio, intervalo))) <=ERRO){
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

		cout << "Usando Método quase-Newton usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoQuaseNewton(polinomio, intervalo) << endl;

		printf("Resultado aplicado no polinomio: %.15Lf \n", polinomio.getResultado(Algoritmo::metodoQuaseNewton(polinomio, intervalo)));

		if(abs(polinomio.getResultado(Algoritmo::metodoQuaseNewton(polinomio, intervalo))) <=ERRO){
			cout << "CORRETO" << endl;
		}else{
			cout << "ERRADO" << endl;
		}

		cout << "----------------------------------------------------" << endl;

	}

	return 0;
}