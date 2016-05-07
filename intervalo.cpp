//Classe de intervalo
class Intervalo{
	private:
		long double inicial;		// Inicío do intervalo
		long double final;		// Final do intervalo
	public:	
		
		/**
		* Descrição: Construtor padrão do programa
		*/
		Intervalo():
		inicial(0),
		final(0)
		{/*Nulo*/}

		/**
		* Descrição: Construtor padrão do programa
		* @params double : Valor inicial do intervalo
		* @params double : Valor final do intervalo
		*/
		Intervalo(long double nInicial,long double nFinal):
		inicial(0),
		final(0)
		{
			this->inicial = nInicial;
			this->final = nFinal;
		}

		/**
		* Descrição: Retorna o valor de início do intervalo
		* @return double : Valor de início do intervalo
		*/
		long double getInicial(){
			return this->inicial;
		}

		/**
		* Descrição: Retorna o valor final do intervalo
		* @return double : Valor final do intervalo
		*/
		long double getFinal(){
			return this->final;
		}

		/**
		* Descrição: Insere um novo valor inicial no intervalo
		* @return double : Novo Valor inicial do intervalo
		*/
		void setInicial(long double nInicial){
			this->inicial = nInicial;
		}

		/**
		* Descrição: Insere um novo valor final no intervalo
		* @return double : Novo Valor final do intervalo
		*/
		void setFinal(long double nFinal){
			this->final = nFinal;
		}
		
};	
