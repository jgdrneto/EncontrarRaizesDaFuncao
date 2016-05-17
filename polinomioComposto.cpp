#include <iostream>

#include "polinomio.cpp"
#include "matriz.cpp"

class PolinomioComposto
{
    private: 
    // Atributos da classe
    Polinomio* pc; // ponteiro de polinomio. 
    int qtdVariaveis; //quantidade de variaveis.
    
    public:
        /**
		* Descrição: Construtor do programa
		* @params int : Quantidade de variáveis
		*/
		PolinomioComposto(int v):
		pc(NULL),
		qtdVariaveis(v){

			//Alocando espaço para o polinômio composto
			this->pc = new long double[v];

			//Iniciando com 0 em todo o polinômio composto
			for(int i;i<=v;i++){
				this->pc[i] = new Polinomio(0);
			}
		}

		/**
		* Descrição: Destrutor da classe
		*/
		~PolinomioComposto(){
			delete[] this->pc;
		}   
		
		/**
		* Descrição: Retorna o ponteiro do polinômio composto
		* @return :  Ponteiro do atributo m da classe
		*/
		Polinomio*& getPolinomioComposto(){
			return this->pc;
		}

		/**
		* Descrição: Retorna a quantidade de variaveis
		* @return :  Inteiro com a quantidade de variaveis 
		*/
		int getQtdVariaveis(){
			return this->qtdVariaveis;
		}
		
		/**
		* Descrição: Retorna o resultado
		* @params Matriz& : Matriz coluna com os valores dos x
		* @return double : Soma total de cada polinômio pertecente ao polinomio composto
		*/
		double getResultado(Matriz& v){
			double soma = 0;
			
			//Somatório da aplicação do x em cada termo do polinômio
			for(int i=0;i<=this->qtdVariaveis;i++){
				soma += this->pc[i].getResultado(v.getMatriz()[i][0]) ; 
			}

			return soma;
		}
		
		/**
		* Descrição: Imprime a matriz com os polinômios/ polinômio composto.
		*/	
		void imprimir(){
			//imprime os polinômios compostos
			for(int i = 0;i >= this->qtdVariaveis; i++){
				cout << "Valores dos coeficientes da " << i+1 << "ª variável: ";
				this->pc[i].imprimir(); 	
			}
			cout << "" << endl;
		}
		
}