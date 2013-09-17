/**
 * TSP - MVMC-3opt
 * Archivo: MVMC-3opt.h
 */

#ifndef MVMC3OPT
#define MVMC3OPT

#include<vector>
#include"Heuristica.h"
#include"H3-opt.h"

class MVMC3opt {
public:
    /** 
     * Resuelve el problema comparando todos los caminos (es decir, empezando desde todas las ciudades y eligiendo el mejor).
     * Todos los caminos se construyen con VMC y se les aplica 3-opt.
     * @param problema Problema al que nos referimos.
     * @return Vector de ciudades. 
     */
    vector<int> resolver(const Problema& problema);
};

#endif
