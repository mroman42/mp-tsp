/**
 * TSP - Problema
 * Archivo: Problema.h
 */

#ifndef PROBLEMA
#define PROBLEMA

#include"Ciudad.h"
#include<vector>
#include<cstdlib>
using namespace std;

/**
 * Contiene toda la informacion relativa al problema almacenada
 * en forma de memoria dinamica (ciudades y distancias entre ellas),
 * facilitando asi la encapsulacion del problema y su manejo por
 * parte de las clases que implementan la heuristica.
 */
class Problema {
private:
    /**
     * Datos de las ciudades que componen el problema.
     */
    Ciudad* ciudades;

    /**
     * Matriz triangular de distancias al cuadrado entre las ciudades.
     * Almacena la distancia entre dos ciudades cualesquiera.
     */
    double** distanciasCuadradas;

    /**
     * Matriz triangular de distancias entre las ciudades.
     * Almacena las distancias ya calculadas para evitar volver a calcular.
     */
    double** distancias;	

    /**
     * Metodo auxiliar que reserva una matriz triangular con 
     * la dimension del problema para almacenar distancias o distancias al cuadrado.
     * @return Puntero a la matriz triangular
     */
    double** reservaMatriz();

public:
    /**
     * Dimension del problema. Numero total de ciudades.
     */
    const int DIMENSION;

    /**
     * Crea un problema dados su dimension y un indice de ciudades.
     * Calcula la matriz de distancias cuadradas 
     * e inicializa la matriz de distancias.
     * @param dimension Dimension del problema.
     * @param ciudades Ciudades sobre las que se creara el problema.
     */
    Problema (int dimension, Ciudad* ciudades);

    /**
     * Devuelve la distancia entre dos ciudades, dados sus indices.
     * Si no esta calculada. Se calculara y se introducira en la tabla de distancias.
     * @param indice1 Indice de la primera ciudad.
     * @param indice2 Indice de la segunda ciudad.
     * @return Distancia entre las ciudades.
     * AVISO: Las ciudades deben ser distintas.
     */
    double distancia (int indice1, int indice2) const;

    /**
     * Devuelve la distancia al cuadrado entre dos ciudades, dados sus indices.
     * @param indice1 Indice de la primera ciudad.
     * @param indice2 Indice de la segunda ciudad.
     * @return Distancia entre las ciudades.
     */
    double distanciaCuadrada (int indice1, int indice2) const;

    /**
     * Devuelve una ciudad del problema dado su indice.
     * @param indice Indice de la ciudad pedida.
     * @return Ciudad del problema pedida.
     */
    inline Ciudad ciudad(int indice) const {
	return ciudades[indice];
    };

    /**
     * Devuelve el coste de realizar un recorrido sobre el problema
     * @param camino Camino a recorrer
     * @return Coste total del camino
     */
    double coste (const vector<int>& camino) const;

    /**
     * Destructor de la clase.
     * Elimina datos relativos a las ciudades que lo componen y distancias entre ellas. 
     */
    ~Problema();
};

#endif
