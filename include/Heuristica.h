/**
 * TSP - Heuristica
 * Archivo: Heuristica.h
 */

#ifndef HEURISTICA
#define HEURISTICA

#include"Problema.h"
#include"MVMC-2opt.h"
#include<vector>
#include<cmath>

/**
 * Implementa los metodos necesarios para aplicar la heuristica del
 * vecino mas cercano al TSP. Esta heuristica construye un camino eligiendo
 * a cada paso la ciudad mas cercana a la actual. Entre los caminos construidos
 * iniciando en cada ciudad, escoge aquel que presente una menor distancia total.
 * Proporciona resultados aceptables con muy poco gasto computacional.
 */
class Heuristica {
private:
    /** 
     * Metodo para hallar la ciudad mas cercana a una dada, que aun no este incluida en el camino. 
     * @param problema Referencia a un problema determinado.
     * @param parcial Ciudades actualmente en uso. 
     * @param indice Indice de la ciudad a la que nos referimos.
     * @return Indice de la ciudad mas cercana sin utilizar. 
     */
    int proximaCiudad (const Problema& problema, const vector<bool>& parcial, int indice);

    /**
     * Resuelve el camino empezando por una ciudad indicada. 
     * @param problema Problema al que nos referimos.
     * @param camino_nuevo Camino sobre el que se sobreescribira.
     * @param indice Ciudad desde la que partimos
     */
    void resolverDesde (const Problema& problema, vector<int>& camino_nuevo, int indice);

public:
    /** 
     * Resuelve el problema comparando todos los caminos (es decir, empezando desde todas las ciudades y eligiendo el mejor).
     * @param problema Problema al que nos referimos.
     */
    vector<int> resolver(const Problema& problema);

    friend class MVMC2opt;
    friend class MVMC3opt;
};
#endif
