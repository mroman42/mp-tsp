/**
 * TSP - Segmentos
 * Archivo: Segmentos.h
 */

#ifndef SEGMENTOS
#define SEGMENTOS

#include<cstdlib>
#include<Ciudad.h>
#include<Problema.h>
#include<cmath>
#include<vector>
#include<list>

/**
 * En esta clase se implementaran los metodos necesarios para resolver el problema
 * con la heuristica que hemos llamado "Segmento". Esta heuristica va contruyendo 
 * segmentos del camino, tomando siempre la distancia mas pequeña que hay entre 
 * dos ciudades. Al final, los segmentos, que podian ser independientes en el proceso
 * de su creacion, se terminaran uniendo y formaran el camino completo. 
 */
class Segmento{
private:
    /**
     * Metodo para ir uniendo, dos a dos, las ciudades cuya distancia sea minima, siempre que se puedan unir,
     * es decir, que no esten en el interior de uno de los segmentos creados previamente. 
     * Ira trabajando sobre la lista, de forma que al final solo quede una lista dentro, que contendra el camino.
     * @param segmentos Referencia a una lista de listas de enteros, que contendra los segmentos del camino. 
     * @param problema Referencia a un problema determinado. 
     */
    void unirMasCercanas(list < list<int> >& segmentos, const Problema& problema);   
  
public: 
    /**
     * Crea la lista con los segmentos unitarios, que seran las ciudades, y resuelve el problema
     * llamando al metodo anterior. Devolvera la solucion como un vector de enteros, con los indices
     * de las ciudades en orden. 
     * @param problema Referencia al problema que se desea resolver. 
     * @return Vector de enteros con los indices de las ciudades. 
     */
    vector <int> resolver(const Problema& problema);

};

#endif
