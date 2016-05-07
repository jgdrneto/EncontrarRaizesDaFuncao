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
* @params int : número do algoritmo que se deseja executar
* @params Polinomio& : Polinômio em que se deseja aplicar o algoritmo	
*/
void aplicarAlgorimo(int escolha, Polinomio& polinomio){

	switch(escolha){
		case 1:
			//algoritmo.imprimirResposta(algoritmo.fatoracaoLUcomPivotacaoParcial(matrizA, matrizB));
		break;
		case 2:
			//algoritmo.imprimirResposta(algoritmo.cholesky(matrizA, matrizB));
		break;
	}
}

/**
* Descrição: Escreve o menu de escolha dos algoritmos no terminal
* @return : Inteiro representando a escolha do usuário
*/

int menu(){
	
	//Inicializando variáveis
	int escolha = 0;	
	//Menu para escolha do métodode refinamento que se deseja utilizar
	do {
		cout << "Qual método de refinamento deseja usar: " << endl;
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
	polinomio.getPolinomio()[0] = -3; 
	polinomio.getPolinomio()[1] = 0;
	polinomio.getPolinomio()[2] = 1;
	//polinomio.getPolinomio()[3] = -5;
	//polinomio.getPolinomio()[4] = 1;    
	
}

//Método principal do programa
int main(int argc, char*argv[]){
	
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
		//aplicarAlgorimo(menu(),algoritmo, polinomio);
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

		cout << "----------------------------------------------------" << endl;

		//método das cordas

		cout << "Usando Método das cordas usando troca de sinal: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomio, intervalo) << endl;

		cout << "----------------------------------------------------" << endl;

		//Verificando soluções por LAGRANGE

		cout << "Usando Método de refinamento por Lagrange: " << endl;
			
		intervalo = Algoritmo::metodoDeLagrange(polinomio);

		cout << "Intervalo: " << intervalo.getInicial() << " e " << intervalo.getFinal() << endl;

		cout << "----------------------------------------------------" << endl;

		//método da bisserção usando Lagrange

		cout << "Usando Método de isolamento de bisserção usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDaBissercao(polinomio, intervalo) << endl;

		cout << "----------------------------------------------------" << endl;

		//método das cordas

		cout << "Usando Método das cordas usando Lagrange: " << endl;

		cout << "Valor da aproximação é: " << Algoritmo::metodoDasCordas(polinomio, intervalo) << endl;

		cout << "----------------------------------------------------" << endl;

		cout << "Resultado: " << polinomio.getResultado(1.73188) << endl;

	}
}