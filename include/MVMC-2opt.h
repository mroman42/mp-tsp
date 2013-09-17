/**
 * TSP - MVMC-2opt
 * Archivo: MVMC-2opt.h
 */

#ifndef MVMC2OPT
#define MVMC2OPT

#include<vector>
#include"Heuristica.h"
#include"H2-opt.h"

class MVMC2opt {
public:
    /** 
     * Resuelve el problema comparando todos los caminos (es decir, empezando desde todas las ciudades y eligiendo el mejor).
     * Todos los caminos se construyen con VMC y se les aplica 2-opt.
     * @param problema Problema al que nos referimos.
	 * @return Vector de ciudades. 
     */
    vector<int> resolver(const Problema& problema);
};

#endif
