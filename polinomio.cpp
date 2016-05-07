//Incluindo biblioteca necessárias
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

//Classe para uso dos algoritmos
class Polinomio{
	private:
		//Atributos da classe
		double* p;	//Ponteiro de ponteiro que será alocado o espaço do polinômio
		int grau;	//Grau do polinômio;

	public:

		/**
		* Descrição: Construtor do programa
		* @params int : Grau do polinômio
		*/
		Polinomio(int g):
		p(NULL),
		grau(g){

			//Alocando espaço para o polinômio
			this->p = new double[g+1];

			//Iniciando com 0 em todo o polinômio
			for(int i;i<=g;i++){
				this->p[i]=0;
			}
		}

		/**
		* Descrição: Destrutor da classe
		*/
		~Polinomio(){
			delete[] this->p;
		}

		/**
		* Descrição: Retorna o ponteiro do polinômio
		* @return : Ponteiro do atributo m da classe
		*/
		double*& getPolinomio(){
			return this->p;
		}

		/**
		* Descrição: Retorna o grau do polinômio
		* @return : Inteiro com o valor do número de linhas da matriz
		*/
		int getGrau(){
			return this->grau;
		}

		/**
		* Descrição: Retorna o grau do polinômio
		* @params Double : Valor que se deseja aplicar ao polinômio
		* @return Double : Resultado do polinômio aplicado ao x informado
		*/
		double getResultado(double x){
			double soma=0;
			//Somatório da aplicação do x em cada termo do polinômio
			for(int i=0;i<=this->grau;i++){
				soma+= this->p[i]*pow(x,i); 
			}

			return soma;
		}

		/**
		* Descrição: Retorna a derivada do polinômio
		* @return Polinomio: A derivada deste polinômio
		*/
		Polinomio& getDerivada(){
			
			Polinomio* pDerivada = NULL;

			if(this->grau!=0){
				//Novo polinômio que guardará a nova derivada	
				pDerivada = new Polinomio((this->grau)-1);	

				//Encontrando a derivada
				for(int i=1;i<=this->grau;i++){
					pDerivada->getPolinomio()[i-1]=i*this->p[i];
				}
			}else{
				pDerivada = new Polinomio(0);
			}
			return *pDerivada; 
		}


		/**
		* Descrição: Adiciona valores númericos double no polinômio
		*/
		void adicionarValores(){

			double valor=0;

			for(int i = grau;i >= 0 ; i--){
					
				cout << "Digite o valor para o termo x^" << i << ": ";
					
				cin >> valor;

				//Adicona o número no termo i do vetor p
				this->p[i] = valor;
			}
		}

		/**
		* Descrição: Imprime o polinômio no terminal
		*/	
		void imprimir(){
			//imprime o polinômio
			for(int i = grau;i >= 0; i--){
				//Imprime o valor de "+" do polinômio, caso tenha
				if(p[i]>0){
					cout << "+";
				}
				cout << this->p[i] << "x^" << i << " "; 	
			}
			cout << "" << endl;
		}


		/**
		* Descrição: Encontra o maior indice dos coeficientes negativos
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor do coeficiente
		*/
		double maiorIndiceNegativo(){
			//Percorre o polinômio de maneira decrecente
			for(int i=this->grau;i>=0;i--){
				//Verifica se o x^i polinômio tem valor negativo
				if(this->p[i]< 0){
					//Retorna o indice se o x^i tem valor negativo
					return i;
				}
			}
			return -1;
		}

		/**
		* Descrição: Encontra o maior valor absoluto dos coeficientes negativos
		* @params Polinomio& : Polinômio que se deseja executar o algoritmo
		* @return double : Valor do coeficiente
		*/
		double maiorValorAbsoluto(){
			//Valor inicial de procura do maior valor absoluto
			double menor = this->p[0];

			//Percorre todo o polinômio
			for(int i=0;i<=this->grau;i++){
				//Verifica se o coeficiente junto do x^i é maior que o valor guardado na variável maior
				if(this->p[i] < menor){
					//Atribui um valor maior na váriável maior.
					menor = this->p[i];
				}
			}
			//Retorna o maior valor absoluto dos coeficientes
			return abs(menor);
		}

		/**
		* Descrição: Verifica se todos os coeficientes são positivos
		* @return double : TRUE caso todos os coeficientes sejam positivos, FALSE caso contrário
		*/
		bool todosCoeficientesPositivos(){
			for(int i=0;i<=this->grau;i++){
				if(this->p[i]<0){
					return false;	
				}
			}

			return true;
		}		
};	