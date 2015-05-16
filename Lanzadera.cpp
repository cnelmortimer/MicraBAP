#include <stdio.h>
#include "MicraBAP.h"

#define LIMITESUPERIOR 101
#define LIMITEINFERIOR -1

class SolucionCandidata{//Ejemplo para un problema sencillo en el que se quiere optimizar y = x [0, 100]
    public:
        SolucionCandidata(void){//<Requerido un constructor predeterminado>
            valor = 0;
        }
        //Los criterios podrian ser funciones externas...
        static bool mejorMaximizar(const SolucionCandidata& unaSolucion, const SolucionCandidata& otraSolucion){
            return unaSolucion.valor > otraSolucion.valor;
        }

        static bool mejorMinimizar(const SolucionCandidata& unaSolucion, const SolucionCandidata& otraSolucion){
            return unaSolucion.valor < otraSolucion.valor;
        }
        //------------------------------------------------
        void generarAleatoriamente(void){//<Metodo fundamental de la busqueda>
            this->valor = rand()%101;
        }

        bool operator > (const SolucionCandidata& str) const{//Requerido para el criterio predeterminado
            return valor>str.valor;
        }

        void setValor(int valor){
            this->valor = valor;
        }

        double obtenerAptitud(){//<Metodo complementario>
            return (double) valor;
        }

        int getValor(void){
            return this->valor;
        }

    private:
        int valor;
};

int main(void){
    MicraBAP<SolucionCandidata> optimizador;
    optimizador.reiniciarSemillasAleatorias();
    SolucionCandidata resultado = optimizador.optimizarPorCiclos(60, SolucionCandidata::mejorMinimizar);
    printf("Mejor Resultado en minimización:\n");
    printf("#Valor = %d\n", resultado.getValor());
    //resultado = optimizador.optimizarPorCiclos(60, SolucionCandidata::mejorMaximizar);//Especificacion de un criterio
    resultado = optimizador.optimizarPorCiclos(60);//El crriterio predeterminado es el de maximizacion
    printf("Mejor Resultado en maximización:\n");
    printf("#Valor = %d\n", resultado.getValor());
    return 0;
}
