#include "intervalo.cpp"
#include "matrizPolinomioComposto.cpp"

//Constante usado no passo do método de troca de sinais
#define PASSO 0.5

//Constante de número de máximos de vezes que se executa o algoritmo
#define TOL 100

//Constante para o máximo de erro que se deseja ter
#define ERRO 0.00001

//Classe static para uso dos algoritmos
class Algoritmo{
	private:

		Algoritmo(){/*NULO*/}
		
		static bool satisfaz(MatrizPolinomioComposto& F, Matriz& xap){
			return F.getResultado(xap).norma()<ERRO;
		}
			
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


		/**
		* Descrição: Método para encontra uma função G para o método do ponto fixo
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo que se deseja verificar que o polinõmio converge
		* @return double : Valor final da cota inferior de Lagrange
		*/
		Polinomio& criarG(Polinomio& polinomio,Intervalo& intervalo){
			
			Polinomio* funcaoG = new Polinomio(polinomio.getGrau());

			for(int i=0;i<=polinomio.getGrau();i++){
				funcaoG->getPolinomio()[i] = polinomio.getPolinomio()[i]; 
			}

			//uma formula para a g
			funcaoG->getPolinomio()[0]+=1;
			
			return *funcaoG;
		}

		/**
		* Descrição: Método para verificar se o polinômio converge usando o método do ponto fixo
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo que se deseja verificar que o polinõmio converge
		* @return double : Valor final da cota inferior de Lagrange
		*/
		static bool converge(Polinomio& polinomio,Intervalo& intervalo){
			return abs(polinomio.getDerivada().getResultado(intervalo.getInicial()))<1 && abs(polinomio.getDerivada().getResultado(intervalo.getFinal()))<1;
		}

		/**
		* Descrição: Método para verificar se o polinomio converge usando o método do ponto fixo
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params long double : Intervalo que se deseja verificar que o polinõmio converge
		* @return double : TRUE caso convirja ou FALSE caso não convirja
		*/
		static bool convergePontoFixo(Polinomio& polinomio,long double inicial){
			return abs(polinomio.getDerivada().getResultado(0))<1;
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
				cerr << "Não é possível aplicar o método para Lagrange " << endl;
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
			long double baixo = intervalo.getInicial();
			long double alto = intervalo.getFinal();
			
			//Valores que guadarão os valores atuais e o valores anteriores 
			long double cn;

			do{
				
				cn = baixo - ((alto-baixo)/(polinomio.getResultado(alto)-polinomio.getResultado(baixo)))*polinomio.getResultado(baixo); 

				if(polinomio.getResultado(cn) * polinomio.getResultado(baixo)>0){
					baixo = cn;
				}else{
					if(polinomio.getResultado(cn)==0){
						return cn;
					}else{
						alto = cn;
					}
				}
			}while(abs(polinomio.getResultado(cn))>ERRO);

			return cn;

		}

		/**
		* Descrição: Método do ponto fixo
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDoPontoFixo(Polinomio& polinomio,Intervalo& intervalo){

			long double resultado=0, resultadoAnt=(intervalo.getInicial()+intervalo.getFinal())/2;

			//Criando polinomio (P(x) = x)
			Polinomio* g = new Polinomio(1);
			g->getPolinomio()[1]=1;

			//Tentando usar método de Newton
			if(polinomio.getDerivada().getResultado(intervalo.getInicial())!=0){
				
				*g = ((*g)*polinomio.getDerivada()) - polinomio;

				//Calculando pelo método do ponto fixo
				do{
					resultado = g->getResultado(resultadoAnt)/polinomio.getDerivada().getResultado(resultadoAnt);
					resultadoAnt = resultado;
				}while(abs(polinomio.getResultado(resultado))>=ERRO);

				return resultado;

			}else{
				//Polinomio de tentativa
				Polinomio tentativa(0);

				//Contador para ajudar na procura da g
				int i=0;

				//Tentando encontrar a g de x para o ponto fixo
				do{
					tentativa = ((*g)*i) + polinomio;
					tentativa = tentativa/i;
					i++;
				}while(!convergePontoFixo(tentativa,intervalo.getInicial()) && i<=11);

				//Se convergiu
				if(i<=10){
					*g = tentativa;
				}else{
					//Caso não se encotre a g anteriormente
					int x=0;
					
					do{
						//Definindo o grau do polinômio
						cout << "\nNão foi possível encontrar uma g ou a g informada não converge, por favor, digite uma nova g:" << endl; 
						cout << "Grau do polinômio: ";
						cin >> x;

						//Criando novo polonômio com o grau informado pelo usuário
						g = new Polinomio(x);

						//Adicionando os valores
						g->adicionarValores();

					}while(!convergePontoFixo(*g,intervalo.getInicial()));
				}	
			}

			//Executando o método do ponto fixo
			do{
				resultado = g->getResultado(resultadoAnt);
				resultadoAnt = resultado;
			}while(abs(polinomio.getResultado(resultado))>=ERRO);

			return resultado;
		}

		/**
		* Descrição: Método de Newton
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static long double metodoDeNewton(Polinomio& polinomio,Intervalo& intervalo){
			
			//Variáveis
			long double xap, xn;

			//Calculando ponto médio
			xap = (intervalo.getInicial() + intervalo.getFinal()) / 2;

			//Verificando condições mínimas necessárias para usar o método de newton
			//Derivada no ponto não pode ser igual a 0.
			if(polinomio.getDerivada().getResultado(xap)==0){
				cerr << "Não é possível aplicar o método de Newton." << endl;
			}else{
				//Econtrando a aproximação
				do{
					//Aplicando método de newton
					xn = xap - (polinomio.getResultado(xap)/polinomio.getDerivada().getResultado(xap));
					xap = xn;
				}while(abs(polinomio.getResultado(xap)) > ERRO);	//Condição de parada f(x)<ERRO
			}

			//Aproximação menor que o ERRO
			return xap;
		}
		
		/**
		* Descrição: Método quase-Newton
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @params Intervalo& : Intervalo em que se deseja procurar o zero da função
		* @return double : zero da função.
		*/		
		static Matriz& metodoQuaseNewton(MatrizPolinomioComposto& F, Matriz& xInicial){
			
			Matriz bap(F.getQtdPc(),F.getQtdPc());

			Matriz deltaF(0,0);
			Matriz deltaX(0,0);
			Matriz u(0, 0);
			Matriz xnovo(0,0);
			Matriz bap_1(0,0);
			
			Matriz* xap =  new Matriz(0,0);  //Compilador reclamou

			(*xap) = xInicial;			// x^(ap) <- x^(inicial) 	
			bap = bap.identidade();  	// B_(ap) <- I
			bap_1 = bap.identidade();   // B_(ap)^(-1) = I
			do{
				
				xnovo = (*xap) - bap_1 * F.getResultado(*(xap)); // x^Novo = x^ap - Bap^(-1)*F(x^(ap))
				
				deltaF = F.getResultado(xnovo) - F.getResultado(*(xap)); // /\F = F(x^(novo)) - F(x^(ap)) 
				
				deltaX = xnovo - (*xap); // /\X = x^(novo) - x^(ap)
				
				u = (deltaF-(bap*deltaX))/(deltaX.transposta()* deltaX); //u = (/\F  - B_(ap) * /\X)/ /\X^T * /\X
			
				bap = bap + (u * deltaX.transposta()); //B_(ap) = B(ap) + u * /\X^T  
				
				bap_1 = bap_1 - (bap_1 * u * deltaX.transposta() *bap_1)/((deltaX.transposta() * bap_1 * u)+1); 
				
				*(xap) = xnovo; //x(ap) = x^(novo)

			}while(!satisfaz(F,(*xap)));

			return *xap;
		}

};	
		