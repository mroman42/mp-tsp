/**
 * TSP - Heuristica
 * Archivo: Heuristica.cpp
 */

#include"Heuristica.h"
using namespace std;

vector<int> Heuristica::resolver (const Problema& problema){
    int dimension = problema.DIMENSION;
    vector<int> solucion;
    vector<int> camino_nuevo;
    solucion.reserve(dimension);
    camino_nuevo.reserve(dimension);

    // Fijamos un primer minimo
    resolverDesde (problema, solucion, 0);
    double coste_minimo = problema.coste(solucion);

    // Comparamos todos los caminos posibles
    for (int i=1; i<dimension; i++){
        resolverDesde(problema, camino_nuevo, i);
        double nuevo_coste = problema.coste(camino_nuevo);

	// Guarda en la solucion el minimo
        if (nuevo_coste < coste_minimo){
            coste_minimo = nuevo_coste;
            solucion.swap(camino_nuevo);
        }
    }

    return solucion;
}

void Heuristica::resolverDesde (const Problema& problema, vector<int>& camino, int indice){
    int dimension = problema.DIMENSION;
    vector<bool> usadas;
    usadas.reserve(dimension);
    camino.clear();

    //Marcamos todas las ciudades como no usadas
    for (int i=0; i<dimension; i++)
	usadas.push_back(false);

    // Creamos el camino pasando en cada paso por la ciudad mas cercana
    int ciudad_actual = indice;
    camino.push_back(ciudad_actual);
    usadas[ciudad_actual] = true;
 
    for (int i=1; i<dimension; i++){
        int nueva_ciudad = proximaCiudad (problema, usadas, ciudad_actual);
        camino.push_back(nueva_ciudad);
	usadas[nueva_ciudad] = true;
        ciudad_actual = nueva_ciudad;
    }
}

int Heuristica::proximaCiudad (const Problema& problema, const vector<bool>& usadas, int indice){
    int dimension = problema.DIMENSION;
    double minima = INFINITY;
    int ciudad_cercana = 0;

    // Comprueba para cada ciudad no usada si puede mejorar la distancia
    for (int i=0; i<dimension; i++){
	if (!usadas[i]){
	    double distanciaCuadrada = problema.distanciaCuadrada(indice, i);

	    if (distanciaCuadrada < minima){
		ciudad_cercana = i;
		minima = distanciaCuadrada;
	    }
	}
    }

    return ciudad_cercana;
}


