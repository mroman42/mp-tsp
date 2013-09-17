/**
 * Práctica - TSP
 * Archivo: main.cpp
 */
 
#include<iostream>
#include<string>
#include<stdexcept>
#include<ctime>
#include<chrono>

#include"Problema.h"
#include"Heuristica.h"
#include"FuerzaBruta.h"
#define LIMITE_FUERZA_BRUTA 12
#include"H2-opt.h"
#include"H3-opt.h"
#include"ioTSP.h"
#include"Insercion.h"
#include"Segmentos.h"
#include"MVMC-2opt.h"
#include"MVMC-3opt.h"

using namespace std;

int main(int argc, char* argv[]){
    // Llamada correcta al comando
    if (argc != 3){
	cout<< "Uso: tsp <archivo> <heuristica>" << endl
	    << "Archivo:\t Nombre del archivo TSP." << endl
	    << "Heuristicas:\n\t '-v' Vecino mas cercano "
            << "            \n\t '-f' Fuerza Bruta"
            << "            \n\t '-o' Vecino mas cercano + 2-OPT" 
            << "            \n\t '-s' Segmentos"
	    << "            \n\t '-t' Segmentos + 2-OPT"
	    << "            \n\t '-p' 2-OPT en bruto"
	    << "            \n\t '-3' 3-OPT en bruto"
	    << "            \n\t '-i' Insercion sobre triangulo"
	    << "            \n\t '-e' Insercion sobre envolvente"
	    << "            \n\t '-m' Multi 2-OPT sobre Vecino mas cercano"
	    << "            \n\t '-w' Vecino mas cercano + 3-OPT"
	    << "            \n\t '-x' 3-OPT sobre Multi 2-OPT"
	    << "            \n\t '-k' Multi 3-OPT sobre Vecino mas cercano"
	    << endl;
	return 0;
    }

    // Mide el tiempo total de lectura y calculo
    chrono::high_resolution_clock::time_point inicio = chrono::high_resolution_clock::now();

    try {
        // Crea el problema y aplica la heuristica.
        Problema problema_actual = leeProblema(argv[1]);
        vector<int> solucion;

	switch (argv[2][1]) {
	case 'v': {
	    // VECINO MAS CERCANO
	    Heuristica vecino_cercano;
	    solucion = vecino_cercano.resolver(problema_actual);
	}; break;
	case 'f': {
	    // FUERZA BRUTA
	    if (problema_actual.DIMENSION > LIMITE_FUERZA_BRUTA) 
		cerr << "AVISO: Usar fuerza bruta no resuelve el problema en tiempo razonable.";
	    FuerzaBruta fuerza_bruta;
	    solucion = fuerza_bruta.resolver(problema_actual);
	}; break;
	case 'p': {
	    // 2-OPT EN BRUTO
	    H2opt heuristica_opt2;
	    solucion.reserve(problema_actual.DIMENSION);
	    for (int i=0; i<problema_actual.DIMENSION; i++)
		solucion.push_back(i);
	    solucion = heuristica_opt2.resolver(problema_actual,solucion);
	}; break;
	case '3' : {
	    // 3-OPT EN BRUTO
	    H3opt heuristica_opt3;
	    solucion.reserve(problema_actual.DIMENSION);
	    for (int i=0; i<problema_actual.DIMENSION; i++)
		solucion.push_back(i);
	    solucion = heuristica_opt3.resolver(problema_actual,solucion);
	}; break;
	case 'w': {
	    // VECINO MAS CERCANO + 3-OPT
	    Heuristica vecino_cercano; 
	    H3opt heuristica_opt3; 
	    solucion = vecino_cercano.resolver(problema_actual); 
	    solucion = heuristica_opt3.resolver(problema_actual,solucion); 
	}; break; 
	case 'o': {
	    // VECINO MAS CERCANO + 2-OPT
	    Heuristica vecino_cercano;
	    H2opt heuristica_opt2;
	    solucion = vecino_cercano.resolver(problema_actual);
	    solucion = heuristica_opt2.resolver(problema_actual,solucion);
	}; break;
	case 's': {
	    // SEGMENTOS
	    Segmento heuristica_segmentos; 
	    solucion = heuristica_segmentos.resolver(problema_actual); 
	}; break;
	case 't': {
	    // SEGMENTOS + 2-OPT
	    Segmento segmentos;
	    H2opt heuristica_opt2; 
	    solucion = segmentos.resolver(problema_actual);
	    solucion = heuristica_opt2.resolver(problema_actual,solucion);
	}; break; 
	case 'i': {
	    // INSERCION
	    Insercion insercion;
	    solucion = insercion.resolver(problema_actual, false);
	}; break;
	case 'e': {
	    // INSERCION CON ENVOLVENTE
	    Insercion insercion;
	    solucion = insercion.resolver(problema_actual, true);
	}; break;
	case 'm': {
	    // VECINO MAS CERCANO / MULTI-2OPT
	    MVMC2opt multi2opt;
	    solucion = multi2opt.resolver(problema_actual);
	}; break;
	case 'x': {
	    // VECINO MAS CERCANO / MULTI-2OPT  + 3OPT
	    MVMC2opt multi2opt;
	    H3opt heuristica_opt3;
	    solucion = multi2opt.resolver(problema_actual);
	    solucion = heuristica_opt3.resolver(problema_actual, solucion);
	}; break;
	case 'k': {
	    // VECINO MAS CERCANO / MULTI-3OPT
	    MVMC3opt multi3opt;
	    solucion = multi3opt.resolver(problema_actual);
	}; break;

	default: throw logic_error ("Heuristica incorrecta.");	
	}
	

	// Muestra la solucion
	muestraRuta (problema_actual, solucion);
	muestraSolucion (problema_actual, solucion);

    } catch (logic_error error){
        cerr << "ERROR: " << error.what() << endl;
    }

    // Muestra el tiempo total de lectura y calculo
    chrono::high_resolution_clock::time_point final = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion_total = chrono::duration_cast<chrono::duration<double>>(final - inicio);
    cout << "# Tiempo total: " << duracion_total.count() << " segundos.\n";
}
