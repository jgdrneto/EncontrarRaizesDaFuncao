#import "polinomio.cpp"

class FracaoPolinomio{
	private:
		Polinomio numerador;
		Polinomio denominador;
	public:
		FracaoPolinomio(Polinomio nNumerador, Polinomio nDenominador):
		numerador(nNumerador),
		denominador(nDenominador){/*NULO*/}



		Polinomio& getNumerador(){
			return this->numerador; 
		}

		Polinomio& getDenominador(){
			return this->denominador; 
		}

		long double getResultado(long double x){
			return this->numerador.getResultado(x)/this->denominador.getResultado(x);
		}
};