//Incluindo biblioteca necessárias
#include <iostream>
#include <algorithm>

using namespace std;

//Classe static para uso dos algoritmos
class Matriz{
	private:
		//Atributos da classe
		double** m;	//Ponteiro de ponteiro no qual será alocado o espaço para matriz
		int l;		//Número de linhas da matriz;
		int c; 		//Número de colunas da matriz;
	public:

		/**
		* Descrição: Construtor do programa
		* @params int : Número de linhas da matriz
		* @params int : Número de colunas da matriz
		*/
		Matriz(int numeroL, int numeroC):
		m(NULL),
		l(0),
		c(0){

			//Atribui o numero de linhas e colunas no atributo correspondente da classe
			this->l= numeroL;
			this->c = numeroC;

			//Alocando espaço para o vetor de ponteiros
			m = new double*[this->l];

			//Alocando espaço para que cada posição do vetor de ponteiros aloque um vetor de números do tipo double
			for(int i=0; i<this->l; i++){
				m[i] = new double[this->c];
			} 
		}

		/**
		* Descrição: Retorna o duplo ponteiro da matriz
		* @return : Duplo ponteiro do atributo m da classe
		*/
		double**& getMatriz(){
			return this->m;
		}

		/**
		* Descrição: Retorna o número de linhas da matriz
		* @return : Inteiro com o valor do número de linhas da matriz
		*/
		int getNumeroL(){
			return this->l;
		}

		/**
		* Descrição: Retorna o número de colunas da matriz
		* @return : Inteiro com o valor do número de colunas da matriz
		*/
		int getNumeroC(){
			return this->c;
		}

		/**
		* Descrição: Destrutor da classe
		*/
		virtual ~Matriz(){
			//Desalocando a memória
			for(int i =0;i<this->l;i++){
				delete[] this->m[i];
			}
		}

		/**
		* Descrição: Adiciona valores numéricos double na matriz
		*/
		void adicionarValores(){
			if(this->m!=NULL){

				double valor=0;

				for(int i = 0;i < this->l; i++){
					for(int j = 0;j < this->c;j++){
						
						cout << "Digite o valor para a linha " << i+1 << " coluna " << j+1 << ": ";
						
						cin >> valor;

						//Adiciona o número na linha i coluna j da matriz
						m[i][j] = valor;
					}
				}

			}else{
				cout << "Espaço para matriz não alocado" << endl;
			}
		}

		void adicionarValores(double valor, int i, int j){
			if(this->m!=NULL){
				//Adicona o número na linha i coluna j da matriz
				m[i][j] = valor;
			}else{
				cout << "Espaço para matriz não alocado" << endl;
			}
		}

		double getValor(int i, int j){
			return m[i][j];
		}

		/**
		* Descrição: Imprimi a matriz no terminal
		*/	
		void imprimir(){
			for(int i = 0;i < this->l; i++){
				for(int j = 0;j < this->c;j++){
					cout << m[i][j] << " ";
				}
				cout << "" << endl;
			}
		}

		/**
		* Descrição: Sobrecarga do operador de atribuição
		* @params: Matriz na qual se deseja fazer a atribuição
		* @return: Endereço da matriz resultante da operação de atribuição
		*/
		void operator=(Matriz& matriz2){
			//Criando nova matriz
			Matriz* resultado = new Matriz(matriz2.getNumeroL(),matriz2.getNumeroC());
			
			//Passando os valores	
			for(int i = 0;i < matriz2.getNumeroL(); i++){
				for(int j = 0;j < matriz2.getNumeroC();j++){
					resultado->getMatriz()[i][j] = matriz2.m[i][j];
				}
			}

			//Atribuindo os valores
			this->m = resultado->getMatriz();
			this->c = resultado->getNumeroC();
			this->l = resultado->getNumeroL(); 
		}

		/**
		* Descrição: Sobrecarga do operador de multiplicação
		* @params: Matriz na qual se deseja fazer a multiplicação
		* @return: Endereço da matriz resultante da operação de multiplicação
		*/
		Matriz& operator*(Matriz& matriz2){

			//Criando a cara da matriz final
			Matriz* resultado = new Matriz(this->l, matriz2.getNumeroC());
			//Criando contador
			double acumula;

			//Verificando se pode fazer a multiplicação de matriz
			if(this->c == matriz2.getNumeroL()){
				//Fazendo a multiplicação de matriz
				for(int l=0;l<this->l;l++){
					for(int c=0;c<matriz2.getNumeroC();c++){
						acumula=0;
						for(int i=0;i<this->c;i++){
							acumula += this->m[l][i] * matriz2.getMatriz()[i][c];
						}
						resultado->getMatriz()[l][c] = acumula;
					}
				}
			}else{
				//Caso não se passe matrizes de número de linhas de this igual ao número de colunas de colunas de matriz2 
				cout << "ERRO: Não é possível fazer a multiplicação dessas matrizes" << endl;
			}

			//retornado matriz resultante da operação
			return *resultado;
		}  

		/**
		* Descrição: Sobrecarga do operador de soma
		* @params: Matriz na qual se deseja fazer a soma
		* @return: Endereço da matriz resultante da operação de soma
		*/
		Matriz& operator+(Matriz& matriz2){

			//Criando a cara da matriz final
			Matriz* resultado = new Matriz(this->l, this->c);

			//Verificando se pode fazer a soma de matriz
			if(this->c == matriz2.getNumeroC() && this->l == matriz2.getNumeroL()){
				//Fazendo a soma de matriz
				for(int l=0;l<this->l;l++){
					for(int c=0;c<this->c;c++){
						resultado->getMatriz()[l][c] = this->m[l][c] + matriz2.getMatriz()[l][c];	
					}	
				}
			}else{
				//Caso não se passe matrizes de número de linhas e colunas iguais
				cout << "ERRO: Não é possível fazer a soma dessas matrizes" << endl;
			}

			//retornado matriz resultante da operação
			return *resultado;
		}

		/**
		* Descrição: Sobrecarga do operador de subtração
		* @params: Matriz na qual se deseja fazer a subtração
		* @return: Endereço da matriz resultante da operação de subtração
		*/
		Matriz& operator-(Matriz& matriz2){

			//Criando a cara da matriz final
			Matriz* resultado = new Matriz(this->l, this->c);

			//Verificando se pode fazer a subtração de matriz
			if(this->c == matriz2.getNumeroC() && this->l == matriz2.getNumeroL()){
				//Fazendo a subtração de matriz
				for(int l=0;l<this->l;l++){
					for(int c=0;c<this->c;c++){
						resultado->getMatriz()[l][c] = this->m[l][c] - matriz2.getMatriz()[l][c];	
					}	
				}
			}else{
				//Caso não se passe matrizes de número de linhas e colunas iguais
				cout << "ERRO: Não é possível fazer a subtração dessas matrizes" << endl;
			}

			//retornado matriz resultante da operação
			return *resultado;
		}

		/**
		* Descrição: Matriz identidade de uma matriz
		* @return: A matriz identidade
		*/
		Matriz& identidade(){

			//Criando a cara da matriz final
			Matriz* resultado = new Matriz(this->l, this->c);			

			//Criando a matriz identidade
			for(int l=0;l<this->l;l++){
				for(int c=0;c<this->c;c++){
					if(l==c){
						resultado->getMatriz()[l][c]=1;
					}else{
						resultado->getMatriz()[l][c]=0;
					}		
				}
			}

			return *resultado;
		}

		/**
		* Descrição: Troca a 1º linha por outra linha passada por parâmetro
		* @params: Linha na qual se deseja trocar com a primeira
		*/
		void trocarLinhas(int linha){

			for(int i=0;i<=this->c-1;i++){
				swap(this->m[0][i], this->m[linha][i]);
			}
			
		}

		/**
		* Descrição: Inverte os valores da diagonal principal
		*/
		void inverteD(){
			if(this->l == this->c){
				for(int i=0;i<this->c;i++){
					this->m[i][i] = (1.0/this->m[i][i]);
				}
			}else{
				cout << "ERRO: Matrizes precisam ter o mesmo valor de linha e coluna" << endl;
			}
		}

		/**
		* Descrição: Transpõe a matriz
		*/
		Matriz& transposta(){
			
			//Nova mariz com os valores da transposta
			Matriz* resultado = new Matriz(this->c, this->l); 	
			
			for(int i=0;i<resultado->getNumeroL();i++){
				for(int j=0;j<resultado->getNumeroC();j++){
					resultado->getMatriz()[i][j] = this->m[j][i];
			 	}	
			}
				
			return *resultado;
		}

		/**
		* Descrição: Encontra a matriz diagonal
		* @return: A matriz diagonal correspondente
		*/
		Matriz& diagonalMat(){

			//Matriz que guardará a diagonal
			Matriz* diagonal = new Matriz(this->l, this->c);


			if(this->l == this->c){
				for(int i=0;i<this->l;i++){
					for(int j=0;j<this->c;j++){
						if(i == j){
							diagonal->getMatriz()[i][j] = this->m[i][j];
						}else{
							diagonal->getMatriz()[i][j] = 0;
						}
					}
				}
			}else{
				cout << "ERRO: Matrizes precisam ter o mesmo valor de linha e coluna" << endl;
			}	
			return *diagonal;	
		}

		/**
		* Descrição: Verifica se a matriz é simátrica
		* @return: TRUE para caso seja simétrica e FALSE caso não seja simátrica
		*/
		bool verificaSimetria(){
			for(int i=0;i<this->l;i++){
				for(int j=0;j<this->c;j++){
					if(this->m[i][j] != this->m[j][i]){
						return false;	
					}
				}	
			}
			return true;
		}

		/**
		* Descrição: Calcula a norma de um matriz coluna
		* @return: double : valor da norma do matriz coluna ou -1 caso não seja uma matriz coluna
		*/
		double norma(){
			if(this->c==1){
				double soma=0;
				//Soma dos termo internos da matriz coluna
				for(int i=0;i<this->l;i++){
					soma += this->m[i][0]*this->m[i][0];
				}
				//Retornando a norma
				return sqrt(soma);
			}else{
				cout << "ERRO: Não é uma matriz coluna" << endl;
				return -1;
			}
		}

		/**
		* Descrição: Encontra o maior valor na matriz 
		* @return: double : maior valor da matriz
		*/
		double maiorValor(){
			double valor=this->m[0][0];
			for(int i=0;i<this->l;i++){
				for(int j=0;j<this->c;j++){
					if(this->m[i][j]>valor){
						valor = this->m[i][j];
					}
				}
			}

			return valor;	
		}
		
		/**
		* Descrição: Multiplica um escalar pela matriz
		* @return: Matriz& : matriz multiplicada
		*/
		Matriz& operator*(double escalar){
			Matriz *resultado = new Matriz(this->l, this->c);
			
			for(int i = 0; i < this->l; i++){
				for(int j = 0; j < this->c; j++){
					resultado->getMatriz()[i][j] = this->getMatriz()[i][j] * escalar;
				}
			}

			return *resultado;
		}

		/**
		* Descrição: Soma um escalar à matriz
		* @return: Matriz& : matriz somada
		*/
		Matriz& operator+(double escalar){
			
			Matriz *resultado = new Matriz(this->l, this->c);
			
			for(int i = 0; i < this->l; i++){
				for(int j = 0; j < this->c; j++){
					resultado->getMatriz()[i][j] = this->getMatriz()[i][j] + escalar;
				}
			}

			return (*resultado);
		}
		
		/**
		* Descrição: Divisão por matriz unária
		* @return: Matriz& : nova matriz com o resultado da operação de divisão 
		*/
		Matriz& operator/(Matriz& matriz){
			//Nova matriz que guardará o resultado
			Matriz *resultado = new Matriz(this->l, this->c);
			
			for(int i = 0; i < this->l; i++){
				for(int j = 0; j < this->c; j++){
					resultado->getMatriz()[i][j] = this->getMatriz()[i][j]/matriz.getMatriz()[0][0];
				}
			}

			return *resultado;
		}
		
};