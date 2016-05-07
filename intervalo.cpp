//Classe de intervalo
class Intervalo{
	private:
		double inicial;		// Inicío do intervalo
		double final;		// Final do intervalo
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
		Intervalo(double nInicial, double nFinal):
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
		double getInicial(){
			return this->inicial;
		}

		/**
		* Descrição: Retorna o valor final do intervalo
		* @return double : Valor final do intervalo
		*/
		double getFinal(){
			return this->final;
		}

		/**
		* Descrição: Insere um novo valor inicial no intervalo
		* @return double : Novo Valor inicial do intervalo
		*/
		void setInicial(double nInicial){
			this->inicial = nInicial;
		}

		/**
		* Descrição: Insere um novo valor final no intervalo
		* @return double : Novo Valor final do intervalo
		*/
		void setFinal(double nFinal){
			this->final = nFinal;
		}
		
};	
