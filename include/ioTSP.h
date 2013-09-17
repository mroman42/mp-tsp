/**
 * TSP - ioTSP
 * Archivo: ioTSP.h
 * 
 * Conjunto de funciones de entrada y salida.
 * Generan problemas y muestran soluciones.
 */

#ifndef IOTSP
#define IOTSP

#include<stdexcept>
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include"Ciudad.h"
#include"Problema.h"

/**
 * Creara un problema a partir de los datos en un fichero. 
 * @param Fichero desde el que leeremos los datos. 
 * @return Problema creado.
 */
Problema leeProblema (const string fichero);

/**
 * Muestra en pantalla las coordenadas del camino mas eficiente, ciudad por ciudad.
 * @param Problema al que nos referimos. 
 * @param Camino como solucion del problema. 
 */
void muestraSolucion (const Problema&, const vector<int>& solucion);

/**
 * Muestra en pantalla la ruta mas eficiente, ciudad por ciudad.
 * @param Problema al que nos referimos. 
 * @param Camino como solucion del problema. 
 */
void muestraRuta (const Problema& problema, const vector<int>& solucion);

#endif
