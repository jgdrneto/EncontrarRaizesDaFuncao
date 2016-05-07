#include "polinomio.cpp"
#include "intervalo.cpp"

//Constante usado no passo do método de troca de sinais
#define PASSO 0.5

//Constante de número de máximos de vezes que se executa o algoritmo
#define TOL 100

//Constante para o máximo de erro que se deseja ter
#define ERRO 0.001

//Classe static para uso dos algoritmos
class Algoritmo{
	private:

		Algoritmo(){/*NULO*/}

		/**
		* Descrição: Método para calcular o valor do coeficiente de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor do coeficiente
		*/
		static long double calcularCoeficiente(Polinomio& polinomio){
			// Formula para calcular o coeficiente, 
			// Pense em: (1 + pow(b,1/e))
			// b : Valor de dentro da raiz
			// e : indice da raiz
			
			/*
			cout << "polinomio: " << endl;
			polinomio.imprimir();
			cout << "Maior valor absoluto dos negativos: " << polinomio.maiorValorAbsoluto() << endl;
			cout << "Coeficiente do termo de maior indice: " << polinomio.getPolinomio()[polinomio.getGrau()] << endl;
			cout << "Grau do polinomio: " << polinomio.getGrau() << endl;
			cout << "Maior indice dos coeficientes negativos: " << polinomio.maiorIndiceNegativo() << endl;
			*/
			
			return 1+pow((polinomio.maiorValorAbsoluto()/polinomio.getPolinomio()[polinomio.getGrau()]),(1 / (polinomio.getGrau()-polinomio.maiorIndiceNegativo())));
		}

		/**
		* Descrição: Método para encontrar o valor inicial do interalo da cota superior de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor inicial da cota superior de Lagrange
		*/
		static long double cotaSupIniLagrange(Polinomio& polinomio){
				
			//Criando um polinômio de mesmo grau.
			Polinomio iniPolinomio = Polinomio(polinomio.getGrau());

			//Inverte os coeficientes do polinômio
			for(int i=0;i<=polinomio.getGrau();i++){
				iniPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[polinomio.getGrau()-i];
			}

			//Verificando se a^n tem sinal negativo
			if(iniPolinomio.getPolinomio()[iniPolinomio.getGrau()]<0){
				//Trocando sinal do polinomio
				for(int i=0; i<=iniPolinomio.getGrau();i++){
					iniPolinomio.getPolinomio()[i]*= -1; 
				}
			}

			//Calcula o coeficiente
			return 1/calcularCoeficiente(iniPolinomio);
		}

		/**
		* Descrição: Método para encontrar o valor final do intervalo da cota superior de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor final da cota superior de Lagrange
		*/
		static long double cotaSupFinDeLagrange(Polinomio& polinomio){

			return calcularCoeficiente(polinomio);
		}

		/**
		* Descrição: Método para encontrar o valor inicial do interalo da cota inferior de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor inicial da cota inferior de Lagrange
		*/
		static long double cotaInfIniLagrange(Polinomio& polinomio){
			
			//Criando um polinômio de mesmo grau.
			Polinomio infIniPolinomio = Polinomio(polinomio.getGrau());

			//Multiplicando os coeficientes dos indices impares por -1;
			for(int i=0;i<=infIniPolinomio.getGrau();i++){
				if(i%2==1){
					infIniPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[i] * (-1); 
				}else{
					infIniPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[i];
				}
			}

			//Inverte os coeficientes do polinômio
			for(int i=0;i<=polinomio.getGrau();i++){
				infIniPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[polinomio.getGrau()-i];
			}

			//Verificando se a^n tem sinal negativo
			if(infIniPolinomio.getPolinomio()[infIniPolinomio.getGrau()]<0){
				//Trocando sinal do polinomio
				for(int i=0; i<=infIniPolinomio.getGrau();i++){
					infIniPolinomio.getPolinomio()[i]*= -1; 
				}
			}

			//Calcula o coeficiente
			return (-1) / calcularCoeficiente(infIniPolinomio);
		}

		/**
		* Descrição: Método para encontrar o valor final do intervalo da cota inferior de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor final da cota inferior de Lagrange
		*/
		static long double cotaInfFinDeLagrange(Polinomio& polinomio){
			//Criando o polinômio que será usado nas contas inferiores
			Polinomio infFinPolinomio =  Polinomio(polinomio.getGrau()); 
			
			//Multiplicando os coeficientes dos indices impares por -1;
			for(int i=0;i<=infFinPolinomio.getGrau();i++){
				if(i%2==1){
					infFinPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[i] * (-1); 
				}else{
					infFinPolinomio.getPolinomio()[i] = polinomio.getPolinomio()[i];
				}
			}

			return calcularCoeficiente(infFinPolinomio);
		}

	public:
		
		/**
		* Descrição: Método de troca de sinal para isolamento
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params double : Valor inicial de procura
		* @return Intervalo& : Intervalo com o valor inicial e final
		*/	
		static Intervalo& metodoTrocaDeSinal(Polinomio& polinomio,double x){
			
			//Procura a troca de sinais TOL vezes
			for(int i=0; i<=TOL;i++){
				if((polinomio.getResultado(x) * polinomio.getResultado(x+PASSO)) > 0){
					x +=PASSO;
				}else{
					break;
				}
				//Excessão para quando a tolerancia for extrapolada
				if(i==TOL){
					cerr << "Erro: Número de tolerância de execuções estrapolado, tente um novo x" << endl;
				}
			}
			//Retorna um novo objeto Intervalo com os valores inicial e final.
			return *(new Intervalo(x, x+PASSO));

		}

		/**
		* Descrição: Método de Lagrange
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return Intervalo& : Tupla com o valor inicial e final
		*/	
		static Intervalo& metodoDeLagrange(Polinomio& polinomio){
			//Verificando condições iniciais para usar Lagrange
			if(polinomio.getPolinomio()[0]!=0){

				//Verificando se a^n tem sinal negativo
				if(polinomio.getPolinomio()[polinomio.getGrau()]<0){
					//Trocando sinal do polinomio
					for(int i=0; i<=polinomio.getGrau();i++){
						polinomio.getPolinomio()[i]*= -1; 
					}
				}

			}else{
				cerr << "Não é possível aplicar o método para Lagrande " << endl;
			}
			
			if(!polinomio.todosCoeficientesPositivos()){
				//Retorna intervalo com os valores inicial e final do intervalo usando o método de Lagrange
				return *(new Intervalo(cotaSupIniLagrange(polinomio), cotaSupFinDeLagrange(polinomio)));
			}

			//Retorna intervalo com os valores inicial e final do intervalo usando o método de Lagrange
			return *(new Intervalo(cotaInfIniLagrange(polinomio), cotaInfFinDeLagrange(polinomio)));
		}

		/**
		* Descrição: Método da bisserção
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDaBissercao(Polinomio& polinomio,Intervalo& intervalo){
			//Atribuindo valores do intervalo
			long double inferior = intervalo.getInicial();
			long double superior = intervalo.getFinal();
			long double pontoM; 

			//Repita até condição de parada	
			do{
				//Pega o ponto médio
				pontoM = (inferior+superior)/2;

				//Verifica se tem mesmo sinal da parte inferior
				if (polinomio.getResultado(inferior)*polinomio.getResultado(pontoM) > 0){
					inferior = pontoM;
				}else{
					//Verifica se o pontoM é o ponto que zera a fũnção
					if(polinomio.getResultado(pontoM)==0){
						return pontoM;
					}else{
						superior = pontoM;
					}
				}

			}while(abs(polinomio.getResultado(pontoM))>ERRO);

			//Retorna valor aproximado
			return pontoM;
		}
		
		/**
		* Descrição: Método das Cordas
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDasCordas(Polinomio& polinomio,Intervalo& intervalo){
			long double inferior = intervalo.getInicial();
			long double superior = intervalo.getFinal();
			//Valores que guadarão os valores atuais e o valores anteriores 
			long double x,c, xAnt;

			//Calculando segunda derivada
			Polinomio segundaDerivada = polinomio.getDerivada().getDerivada();

			//Vendo por onde se partir para construçãõ das cordas
			if(segundaDerivada.getResultado(superior) * polinomio.getResultado(superior) > 0){
				x = superior;
				c = inferior;
			}else{
				x = inferior;
				c = superior;
			}

			do{
				//Salvando o x anterior para cálculo do erro
				xAnt = x;
				//Formula	
				x = xAnt - (polinomio.getResultado(x)/(polinomio.getResultado(x)-polinomio.getResultado(c)))*(x-c);
				/*
				cout << "Valor de x:" << x <<  endl;
				cout << "Valor de x anterior:" << xAnt << endl;
				cout << "-----------------------------------------------------" << endl;
				*/
			}while(abs(polinomio.getResultado(x))>ERRO);

			return x;

		}

		/**
		* Descrição: Método do ponto fixo
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDoPontoFixo(Polinomio& polinomio,Intervalo& intervalo){
			return 0;
		}

		/**
		* Descrição: Método de Newton
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDeNewton(Polinomio& polinomio,Intervalo& intervalo){
			return 0;
		}

};	
		