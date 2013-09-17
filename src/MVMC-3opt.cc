/**
 * TSP - MVMC-3opt
 * Archivo: MVMC-3opt.cpp
 */

#include"MVMC-3opt.h"
using namespace std;

vector<int> MVMC3opt::resolver (const Problema& problema){
    H3opt Heuristica_3opt;
    Heuristica Heuristica_VMC;

    int dimension = problema.DIMENSION;
    vector<int> solucion;
    vector<int> camino_nuevo;
    solucion.reserve(dimension);
    camino_nuevo.reserve(dimension);

    // Fijamos un primer minimo
    Heuristica_VMC.resolverDesde (problema, solucion, 0);
    solucion = Heuristica_3opt.resolver (problema, solucion);
    double coste_minimo = problema.coste(solucion);

    // Comparamos todos los caminos posibles
    for (int i=1; i<dimension; i++){
        Heuristica_VMC.resolverDesde (problema, camino_nuevo, i);
	camino_nuevo = Heuristica_3opt.resolver (problema, camino_nuevo);
        double nuevo_coste = problema.coste(camino_nuevo);

	// Guarda en la solucion el minimo
        if (nuevo_coste < coste_minimo){
            coste_minimo = nuevo_coste;
            solucion.swap(camino_nuevo);
        }
    }

    return solucion;
};
