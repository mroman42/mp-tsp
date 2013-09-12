#ifndef CIUDAD
#define CIUDAD


#include <cmath>
#define SQUARE(A) (A)*(A)

/**
 * Una ciudad es un punto en el plano del que se almacenan sus coordenadas. 
 * Los conjuntos de ciudades forman los mapas que representan el problema.
 */
struct Ciudad {
    double x;
    double y;

    /**
     * Calcula la distancia euclídea al cuadrado a otra ciudad.
     * @param destino Ciudad a la que se calcula la distancia.
     * @return Distancia total calculada.
     */
    inline double distanciaCuadrado(const Ciudad& destino) const {
	return SQUARE(x - destino.x) + SQUARE(y - destino.y);
    };
};



#endif
