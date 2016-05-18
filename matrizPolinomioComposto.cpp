#include <iostream>

#include "polinomioComposto.cpp"

class MatrizPolinomioComposto
{
    private:
    // Atributos da classe
    PolinomioComposto* mpc;  //ponteiro de polinomio composto.
    int qtdPc;              //quantidade de polinomio composto.
    
    public:
        /**
		* Descrição: Construtor do programa
		* @params int : Quantidade de variáveis
		*/
		MatrizPolinomioComposto(int qtdPolinomioComposto, Matriz& graus):
		mpc(NULL),
		qtdPc(qtdPolinomioComposto){

			//Alocando espaço para o polinômio composto
			this->mpc = new PolinomioComposto[qtdPolinomioComposto];
			//PolinomioComposto *p;
		
			for(int i=0;i<qtdPolinomioComposto; i++){
				//p = new PolinomioComposto(qtdPolinomioComposto, graus.getMatriz()[i][0]);
				this->mpc[i] = *(new PolinomioComposto(qtdPolinomioComposto, graus.getMatriz()[i][0]));
			}
		}

		/**
		* Descrição: Destrutor da classe
		*/
		~MatrizPolinomioComposto(){
			delete[] this->mpc;
		}   
		
		/**
		* Descrição: Retorna o ponteiro da matriz de polinômio composto
		* @return :  Ponteiro do atributo mpc da classe
		*/
		PolinomioComposto*& getMatrizPolinomioComposto(){
			return this->mpc;
		}

		/**
		* Descrição: Retorna a quantidade de polinômios
		* @return :  Inteiro com a quantidade de polinômios
		*/
		int getQtdPc(){
			return this->qtdPc;
		}
		
		/**
		* Descrição: Retorna o resultado da matriz coluna da varíáveis aplicado em cada polinômios
		* @params Matriz& : Matriz coluna com os valores dos x
		* @return Matriz& : Soma total de cada polinômio pertecente ao polinomio composto
		*/
		Matriz& getResultado(Matriz& v){

			Matriz* soma = new Matriz(qtdPc,1);

			//Somatório da aplicação do x em cada termo do polinômio
			for(int i = 0; i < this->qtdPc; i++){
				soma->getMatriz()[i][0] += this->mpc[i].getResultado(v);
			}

			return *soma;
		}
		
};