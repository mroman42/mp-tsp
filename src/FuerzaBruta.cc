/**
 * TSP - Fuerza Bruta
 * Archivo: FuerzaBruta.cpp
 */

#include"FuerzaBruta.h"
using namespace std;

vector<int> FuerzaBruta::resolver (const Problema& problema){
    int dimension = problema.DIMENSION;
    double coste_actual;
    double coste_minimo;
    vector<int> solucion;
    vector<int> camino;
    solucion.reserve(dimension);
    camino.reserve(dimension);

    // Rellena el camino
    for (int i=0; i<dimension; i++)
	camino.push_back(i);
    solucion = camino;
    coste_minimo = problema.coste(camino);

    // Prueba todas las permutaciones
    while (next_permutation(camino.begin(), camino.end())){
	coste_actual = problema.coste(camino);

	if (coste_actual < coste_minimo){
	    solucion = camino;
	    coste_minimo = coste_actual;
	}
    }
    
    return solucion;
}
