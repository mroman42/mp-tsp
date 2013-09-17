/**
 * TSP - 2-OPT
 * Archivo: H2-opt.h
 */

#ifndef H2OPT
#define H2OPT

#include<list>
#include<vector>
#include"Problema.h"

using namespace std;

/**
 * Esta clase implementa los metodos necesarios para la aplicacion de la heuristica
 * 2OPT sobre una solucion parcial ya dada. Esta heuristica toma un camino e intercambia
 * sobre el aquellos caminos entre dos ciudades que se cruzan con otro, reduciendo la distancia en cada intercambio.
 * El algoritmo se termina cuando no pueden intercambiar mas caminos.
 * Al aplicarse sobre la resolucion de la heuristica del vecino mas cercano proporciona buenos resultados sin afectar
 * gravemente al tiempo que tarda en resolverse.
 */
class H2opt {
private:
    /**
     * Resuelve una vez convertida la lista en un camino.
	 * @param problema Problema a resolver. 
     * @param camino Lista que contiene los indices de las ciudades. 
     */
    void resolverLista (const Problema& problema, list<int>& camino);
public:
    /**
     * Resuelve un problema dado usando la heuristica OPT-2 sobre una solucion parcial ya dada.
     * Intercambiara las parejas de caminos que se crucen para conseguir reducir la distancia total.
     * Información en Wikipedia: http://en.wikipedia.org/wiki/2-opt
     * @param problema Problema a resolver.
     * @param solucion_parcial Solucion parcial de partida. Se sobreescribe por el problema dado.
     */
    vector<int> resolver(const Problema& problema, const vector<int>& solucion_parcial);

    friend class H3opt;
};

#endif
