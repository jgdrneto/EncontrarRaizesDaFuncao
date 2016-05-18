//Incluindo biblioteca necessárias
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

//Classe para uso dos algoritmos
class Polinomio{
	private:
		//Atributos da classe
		long double* p;	//Ponteiro de ponteiro que será alocado o espaço do polinômio
		int grau;	    //Grau do polinômio;

	public:

		/**
		* Descrição: Construtor do programa
		* @params int : Grau do polinômio
		*/
		Polinomio():
		p(NULL),
		grau(0)
		{
			//Criando polinômio padrão
			this->p = new long double[1];

			//Adicionando valor inicial
			this->p[0]=0;
			
		}

		/**
		* Descrição: Construtor do programa
		* @params int : Grau do polinômio
		*/
		Polinomio(int g):
		p(NULL),
		grau(g){

			//Alocando espaço para o polinômio
			this->p = new long double[g+1];

			//Iniciando com 0 em todo o polinômio
			for(int i = 0;i<=g;i++){
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
		* @return :  Ponteiro do atributo m da classe
		*/
		long double*& getPolinomio(){
			return this->p;
		}

		/**
		* Descrição: Retorna o grau do polinômio
		* @return :  Inteiro com o valor do número de linhas da matriz
		*/
		int getGrau(){
			return this->grau;
		}

		/**
		* Descrição: Retorna o grau do polinômio
		* @params Double : Valor que se deseja aplicar ao polinômio
		* @return Double : Resultado do polinômio aplicado ao x informado
		*/
		long double getResultado(long double x){
			long double soma=0;

			//Somatório da aplicação do x em cada termo do polinômio
			for(int i = 0; i <= this->grau; i++){
				soma+= this->p[i] * (long double)pow(x,i); 
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

			long double valor=0;

			for(int i = grau;i >= 0 ; i--){
					
				cout << "Digite o valor para o termo x^" << i << ": ";
					
				cin >> valor;

				//Adiciona o número no termo i do vetor p
				this->p[i] = valor;
			}
		}

		/**
		* Descrição: Imprime o polinômio no terminal
		*/	
		void imprimir(){
			//imprime o polinômio
			for(int i = grau;i >= 0; i--){
				//Imprime o valor de "+" do polinômio, caso exista
				if(p[i]>=0){
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
		long double maiorIndiceNegativo(){
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
		long double maiorValorAbsoluto(){
			//Valor inicial de procura do maior valor absoluto
			long double menor = this->p[0];

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
		
		/**
		* Descrição: Sobrecarga do operador de multiplicação
		* @Params Polinomio& : Polinomio que se deseja multiplicar
		* @return Polinomio& : Novo polinômio resultante da multiplicação
		*/
		Polinomio& operator*(Polinomio& polinomio){
			
			//Criando o polinômio resultante
			Polinomio* resultado = new Polinomio(this->grau+polinomio.getGrau());
			
			//Verificando se um dos polinômios é nulo
			if((this->grau == 0 && this->p[0]==0)||(polinomio.getGrau()==0 && polinomio.getPolinomio()[0]==0)){
				resultado = new Polinomio(0);
			}else{
				//Salvando os valores no novo polinômio
				for(int i=0;i<=this->grau;i++){
					for(int j=0; j<=polinomio.getGrau();j++){
						resultado->getPolinomio()[i+j] = resultado->getPolinomio()[i+j] + this->p[i]*polinomio.getPolinomio()[j];
					}
				}
			}	
			return *(resultado);
		}

		/**
		* Descrição: Sobrecarga do operador de multiplicação por número
		* @Params long double : Polinomio que se deseja multiplicar
		* @return Polinomio& :  Novo polinômio resultante da multiplicação
		*/
		Polinomio& operator*(long double numero){
			//Criando novo polinômio			
			Polinomio* resultado = new Polinomio(this->grau); 

			//Atribuindo valores do polinômio para o novo
			*(resultado) = *(this);

			//Multiplicando tudo pelo numero
			for(int i=0;i<=this->grau;i++){
				resultado->getPolinomio()[i]*=numero;
			}

			return *(resultado);
		}

		/**
		* Descrição: Sobrecarga do operador de divisão por número
		* @Params long double : Polinomio que se deseja multiplicar
		* @return Polinomio& :  Novo polinômio resultante da multiplicação
		*/
		Polinomio& operator/(long double numero){
			if(numero!=0){

				//Criando novo polinômio			
				Polinomio* resultado = new Polinomio(this->grau); 

				//Atribuindo valores do polinômio para o novo
				*(resultado) = *(this);

				//Multiplicando tudo pelo numero
				for(int i=0;i<=this->grau;i++){
					resultado->getPolinomio()[i]= resultado->getPolinomio()[i]/numero;
				}

				return *resultado;

			}else{
				cerr << "ERRO: não existe número real em divisão por 0" << endl;
			}

			return *(new Polinomio(0));
		}

		/**
		* Descrição: Sobrecarga do operador de soma
		* @Params Polinomio& : Polinomio que se deseja somar
		* @return Polinomio& : Novo polinômio resultante da soma
		*/
		Polinomio& operator+(Polinomio& polinomio){
			
			Polinomio* resultado = NULL;
			
			long double grauMenor=0;

			if(this->grau >= polinomio.getGrau()){

				//Alocando espaço a partir do maior deles
				resultado = new Polinomio(this->grau);
				
				grauMenor =polinomio.getGrau();

				//Somando a parte em que um deles não te mais coeficientes
				for(int i =polinomio.getGrau()+1; i<=this->grau;i++){
					resultado->getPolinomio()[i] = this->p[i];
				}

			}else{
				//Alocando espaço a partir do maior deles
				resultado = new Polinomio(polinomio.getGrau());

				grauMenor= this->grau;

				//Somando a parte em que um deles não te mais coeficientes
				for(int i =this->grau+1; i<=polinomio.getGrau();i++){
					resultado->getPolinomio()[i] = polinomio.getPolinomio()[i];
				}
			}

			//Somando os dois até achar o menor deles	
			for(int i =0; i<=grauMenor;i++){
				resultado->getPolinomio()[i] = this->p[i]+polinomio.getPolinomio()[i];
			}

			return *resultado;
		}

		/**
		* Descrição: Sobrecarga do operador de atribuição
		* @Params Polinomio& : Polinomio que se deseja copiar
		* @return Polinomio& : Novo polinômio resultante da cópia
		*/
		void operator=(Polinomio& polinomio){

			//Criando novo polinomio de mesmo grau
			Polinomio* resultado = new Polinomio(polinomio.getGrau());

			//Passando valores para o novo polinomio
			for(int i=0; i <=polinomio.getGrau();i++){
				resultado->getPolinomio()[i] = polinomio.getPolinomio()[i];
			}
		
			//Atualizando os valores de this
			this->grau = resultado->getGrau();
			this->p = resultado->getPolinomio();
				
		}

		/**
		* Descrição: Sobrecarga do operador de inversão unário
		* @return Polinomio& : Novo polinômio resultante da inversão
		*/
		Polinomio& operator-(){
			
			//Criando novo polinomio
			Polinomio* inverso = new Polinomio(this->grau);

			//Atribuição usando sobrecarga do operador=
			*(inverso)=*(this);

			//invertendo os valores
			for(int i=0;i<=inverso->getGrau();i++){
				inverso->getPolinomio()[i]*= -1;
			}

			return *(inverso); 
		}

		/**
		* Descrição: Sobrecarga do operador de subtração binário
		* @Params Polinomio& : Polinomio que se deseja subtrair dele
		* @return Polinomio& : Novo polinômio resultante da subtração
		*/
		Polinomio& operator-(Polinomio& polinomio){
			//NÃO CONCLUIDO AINDA

			return *(this) + (-polinomio); 
		}

};	