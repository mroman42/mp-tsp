/**
 * TSP - Problema
 * Archivo: Problema.cpp
 */

#include"Problema.h"
using namespace std;

Problema::Problema (int dimension, Ciudad* ciudades_leidas)
    :ciudades(ciudades_leidas), DIMENSION(dimension)
{
    // Distancias al cuadrado.
    // Reserva la matriz triangular de distancias cuadradas
    distanciasCuadradas = reservaMatriz();

    // Escribe las distancias cuadradas en la matriz triangular
    for (int i=1; i<DIMENSION; i++)
        for (int j=0; j<i; j++)
            distanciasCuadradas[i][j] = ciudades[i].distanciaCuadrado(ciudades[j]);


    // Distancias.
    // Reserva la matriz triangular de distancias
    distancias = reservaMatriz();

    // Inicializa la matriz de distancias triangular
    for (int i=1; i<DIMENSION; i++)
	for (int j=0; j<i; j++)
	    distancias[i][j] = 0;
}

double** Problema::reservaMatriz (){
    // Reserva el total de espacio necesario
    long long int celdas_totales = ((DIMENSION)*(DIMENSION-1))/2;
    double** matriz = new double*[DIMENSION];
    matriz[0] = new double[celdas_totales];

    // Ubica los punteros sobre la matriz triangular
    int tope = DIMENSION - 1;
    for (long long int i=0; i<tope; i++)
	matriz[i+1] = matriz[i] + i;

    return matriz;
}



double Problema::distanciaCuadrada (int indice1, int indice2) const{
    // Consulta la distancia en la matriz cuadrada
    if (indice1 > indice2)
	return distanciasCuadradas[indice1][indice2];
    else
	return distanciasCuadradas[indice2][indice1];
}


double Problema::distancia (int indice1, int indice2) const{
    // Ordena los indices
    int i, j;
    if (indice1 > indice2){
	i = indice1; j = indice2;
    } else {
	i = indice2; j = indice1;
    }

    // Se calcula y almacena si es necesario
    if (distancias[i][j] == 0)
	distancias[i][j] = sqrt(distanciasCuadradas[i][j]);

    return distancias[i][j];
}


double Problema::coste (const vector<int>& camino) const{
    // Suma el coste de todas las aristas
    double coste = 0;
    int tope = camino.size();
    
    for (int i=1; i<tope; i++)
	coste += distancia(camino[i-1],camino[i]);
    coste += distancia(camino[tope-1],camino[0]);

    return coste;
}



Problema::~Problema(){
    // Borra la lista de ciudades
    delete [] ciudades;
    ciudades = NULL;

    // Borra la matriz de distancias cuadradas
    delete [] distanciasCuadradas[0];
    delete [] distanciasCuadradas;
    distanciasCuadradas = NULL;
    
    // Borra la matriz de distancias
    delete [] distancias[0];
    delete [] distancias;
    distancias = NULL;
}

