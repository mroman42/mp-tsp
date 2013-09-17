/**
 * TSP - Insercion
 * Archivo: Insercion.h
 */

#ifndef INSERCION
#define INSERCION

#include<list>
#include<vector>
#include<algorithm>
#include"Problema.h"
#include<iostream>
#include<stack>
using namespace std;

/**
 * Implementa los metodos necesarios para aplicar la heuristica de insercion
 * a un problema del TSP. Es decir, tomara un recorrido inicial (un triangulo 
 * formado por puntos extremos) e insertara las otras ciudades en el por el 
 * metodo de "Insercion mas Economica"; insertando la ciudad que menor aumento
 * de distancia produzca en el mejor sitio posible.
 */
class Insercion {
private:
    /**
     * Crea un triangulo con los puntos extremos:
     * arriba, izquierda, derecha
     * que servira como patron para la heuristica de insercion
     * @param problema Problema a tratar.
     * @param usadas Lista de ciudades usadas.
     * @return Camino con el triangulo creado.
     */
    list<int> crearTriangulo (const Problema& problema, vector<bool>& usadas);

    /**
     * Crea la envolvente convexa de los puntos del problema,
     * que servira como patron para la heuristica de insercion.
     * @param problema Problema a tratar.
     * @param usadas Lista de ciudades usadas.
     * @return Envolvente convexa de las ciudades.
     */
	list<int> crearEnvolvente (const Problema& problema, vector<bool>& usadas);

    /**
     * Calcula la componente vertical del producto vectorial "ba x bc".
     * El signo de esta componente indica el sentido de giro  (a-b-c) entre esos tres puntos.
     * Devolvera positivo si el giro es contra las agujas del reloj.
     * Devolvera negativo si el giro es con las agujas del reloj.
     * Devuelve 0 con puntos colineales.
     * @param a Indice de ciudad.
     * @param b Indice de ciudad.
     * @param c Indice de ciudad.
     * @param problema Problema a resolver.
     * @return Sentido del giro dado por un real. 
     */
    double giro (const int a, const int b, const int c, const Problema& problema);
    
    /**
     * Verdadero cuando la tangente de a con respecto a la primera ciudad
     * es menor que la tangente de b respecto a la primera ciudad.
     * @param problema Problema a resolver.
     * @param a Primera ciudad a comparar.
     * @param b Segunda ciudad a comparar.
     * @param primera_ciudad Ciudad que marca el origen de coordenadas.
     * @return Verdadero si tan(p,a) <= tan(p,b).
     */
    bool angulo_menor (const int a, const int b, const Problema& problema, const int primera_ciudad);

public:
    /**
     * Resuelve el problema usando la heuristica de insercion.
     * @param problema Problema a resolver
     * @param envolvente Verdadero si se quiere usar la envolvente convexa. En caso contrario se usara un triangulo.
     * @return Camino solucion del problema
     */
    vector<int> resolver (const Problema& problema, bool envolvente);
};

#endif
