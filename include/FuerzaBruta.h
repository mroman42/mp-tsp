/**
 * TSP - Fuerza Bruta
 * Archivo: FuerzaBruta.h
 */

#ifndef FUERZABRUTA
#define FUERZABRUTA

#include<cmath>
#include<algorithm>
#include<iostream>
#include"Problema.h"
using namespace std;

/**
 * Esta clase implementa los metodos necesarios para usar el 
 * metodo de fuerza bruta en la resolución de problemas. Este
 * metodo consiste en la comprobacion ordenada de cada camino
 * posible, escogiendo entre todos los posibles el que presenta
 * una menor distancia total. Asegura, por tanto, que la solucion
 * obtenida es optima. Presenta el problema de ser muy costosa computacionalmente,
 * por lo que no puede usarse sobre problemas de gran dimension en un
 * tiempo razonable.
 */
class FuerzaBruta {
public:
    /**
     * Resuelve el problema usando fuerza bruta, esto es, probando todas las soluciones posibles al mismo.
     * @param problema Problema a resolver.
     * @return Solucion optima.
     */
    vector<int> resolver (const Problema& problema);
};

#endif
