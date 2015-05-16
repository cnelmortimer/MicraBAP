#ifndef MICRABAP_H_INCLUDED
#define MICRABAP_H_INCLUDED

#include <stdlib.h>//Para numeros aleatorios
#include <ctime>//Para iniciar la semilla con el tiempo

//Acerca de: Libreria para aplicar procesos de optimizacion por busqueda aleatoria pura.
//Autor: Nicolas C
//Version: 2.0 .- Incluida compatibilidad a nivel de individuo con MicraGENETIC

template <class T> class MicraBAP{
    public:
        MicraBAP(void);//La clase "SolucionCandidata" debe establecer el criterio de optimizacion (maximizar/minimizar)
        //Metodos configurables:
        T optimizarPorCiclos(int nCiclos, bool (*mejor)(const T& a, const T& b));
        T optimizacionMixta(int nCiclos, double aptitudAceptable, bool (*mejor)(const T& a, const T& b));
        //Metodos predeterminados -> maximizacion:
        T optimizarPorCiclos(int nCiclos);
        T optimizacionMixta(int nCiclos, double aptitudAceptable);
        void reiniciarSemillasAleatorias();
};

template <class T> MicraBAP<T>::MicraBAP(void){}

template <class T> T MicraBAP<T>::optimizarPorCiclos(int nCiclos, bool (*mejor)(const T& a, const T& b)){
    T mejorSolucion;
    mejorSolucion.generarAleatoriamente();
    T nuevaSolucion;
    for(int i = 0; i<nCiclos; i++){
        nuevaSolucion.generarAleatoriamente();
        if(mejor(nuevaSolucion, mejorSolucion)){
            mejorSolucion = nuevaSolucion;
        }
    }
    return mejorSolucion;
}

template <class T> T MicraBAP<T>::optimizacionMixta(int nCiclos, double aptitudAceptable,
                                                        bool (*mejor)(const T& a, const T& b)){
    T mejorSolucion;
    mejorSolucion.generarAleatoriamente();
    T nuevaSolucion;
    double aptitudObtenida = mejorSolucion.obtenerAptitud();
    int ciclosUsados = 0;
    while(ciclosUsados<nCiclos && aptitudObtenida<aptitudAceptable){
        nuevaSolucion.generarAleatoriamente();
        if(mejor(nuevaSolucion, mejorSolucion)){
            mejorSolucion = nuevaSolucion;
            aptitudObtenida = nuevaSolucion.obtenerAptitud();
        }
        ciclosUsados++;
    }
    return mejorSolucion;
}
//Metodos predeterminados: Maximizacion...
template <class T> T MicraBAP<T>::optimizarPorCiclos(int nCiclos){
    T mejorSolucion;
    mejorSolucion.generarAleatoriamente();
    T nuevaSolucion;
    for(int i = 0; i<nCiclos; i++){
        nuevaSolucion.generarAleatoriamente();
        if(nuevaSolucion > mejorSolucion){
            mejorSolucion = nuevaSolucion;
        }
    }
    return mejorSolucion;
}

template <class T> T MicraBAP<T>::optimizacionMixta(int nCiclos, double aptitudAceptable){
    T mejorSolucion;
    mejorSolucion.generarAleatoriamente();
    T nuevaSolucion;
    double aptitudObtenida = mejorSolucion.obtenerAptitud();
    int ciclosUsados = 0;
    while(ciclosUsados<nCiclos && aptitudObtenida<aptitudAceptable){
        nuevaSolucion.generarAleatoriamente();
        if(nuevaSolucion > mejorSolucion){
            mejorSolucion = nuevaSolucion;
            aptitudObtenida = nuevaSolucion.obtenerAptitud();
        }
        ciclosUsados++;
    }
    return mejorSolucion;
}

template <class T> void MicraBAP<T>::reiniciarSemillasAleatorias(){
    srand48(time(NULL));
    srand(time(NULL));
}

#endif // MICRABAP_H_INCLUDED
