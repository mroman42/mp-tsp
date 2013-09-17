/**
 * TSP - 3-OPT
 * Archivo: H3-opt.h
 */

#ifndef H3OPT
#define H3OPT

#include<list>
#include<vector>
#include"H2-opt.h"
#include"Problema.h"

typedef list<int>::iterator Lit;
using namespace std;

/**
 * Esta clase implementa los metodos necesarios para la aplicacion de la heuristica
 * 3OPT sobre una solucion parcial ya dada. Esta heuristica toma un camino e intercambia
 * sobre el aquellos grupos de tres caminos entre ciudades que se cruzan entre si, reduciendo la distancia con cada intercambio.
 * Probara sobre el camino los 8 posibles intercambios de caminos.
 * El algoritmo se termina cuando no pueden intercambiar mas caminos.
 * Para preparar el camino, aplica primero la heuristica 2opt.
 */
class H3opt {
private:
public:
    /**
     * Resuelve un problema dado usando la heuristica OPT-3 sobre una solucion parcial ya dada. 
     * @param problema Problema a resolver.
     * @param solucion_parcial Solucion parcial de partida. Se sobreescribe por el problema dado.
     * @return Camino resuelto. 
     */
    vector<int> resolver(const Problema& problema, const vector<int>& solucion_parcial);
	
    /** 
     * Llama al metodo encargado de mejorar el camino hasta que no se puede mejorar mas. 
     * @param problema Problema al que nos referimos. 
     * @param camino Camino sobre el que trabajamos. 
     */
    void resolverLista(const Problema& problema, list<int>& camino);

    /**
     * Ejecuta los cambios pertinentes en la lista para mejorarla. 
     * @param problema Problema al que nos referimos. 
     * @param camino Camino sobre el que trabajamos. 
     * @param continuar Parametro booleano que indica a resolverLista si debe continuar. 
     */
    void mejorarLista (const Problema& problema, list<int>& camino, bool& continuar);


    /** 
     * Devuelve, en caso de existir, el mejor cambio en el camino para que mejorarLista lo ejecute. 
     * @param problema Problema al que nos referimos. 
     * @param camino Camino sobre el que trabajamos.
     * @param punto1 Primer punto de corte.
     * @param punto2 Segundo punto de corte.
     * @param punto3 Tercer punto de corte.
     */
    int combinacionMejor (const Problema& problema, list<int>& camino, Lit punto1, Lit punto2, Lit punto3);

    friend class MVMC3opt;
};



#endif
