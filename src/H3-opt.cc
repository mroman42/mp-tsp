/**
 * TSP - 3-OPT
 * Archivo: H3-opt.cpp
 */

#include"H3-opt.h"

using namespace std;
typedef list<int>::iterator Lit;


vector<int> H3opt::resolver(const Problema& problema, const vector<int>& solucion_parcial){
    // Trabajaremos el camino en una lista enlazada
    list<int> camino;
    for (int i=0; i<problema.DIMENSION; i++)
	camino.push_back(solucion_parcial[i]);

    // Aplica el algoritmo
    resolverLista(problema, camino);

    // Devuelve el camino como un array normal
    vector<int> solucion;
    solucion.reserve(problema.DIMENSION);
    for (Lit i = camino.begin(); i != camino.end(); ++i)
	solucion.push_back(*i);

    return solucion;
}

void H3opt::resolverLista(const Problema& problema, list<int>& camino){
    bool continuar = true;
    H2opt heuristica2opt;

    // Aplicara el algoritmo hasta que no haya cambios
    while (continuar){
	continuar = false;
	heuristica2opt.resolverLista(problema, camino);
	mejorarLista(problema, camino, continuar);
    }
}

void H3opt::mejorarLista (const Problema& problema, list<int>& camino, bool& continuar){
    // Ubica el primer punto
    Lit punto1        = camino.begin();
    Lit siguiente1    = punto1;         ++siguiente1;
    Lit possiguiente1 = siguiente1;     ++possiguiente1;

    while (possiguiente1 != camino.end()){
	// Ubica el segundo punto
	Lit punto2 = possiguiente1;
	Lit siguiente2 = punto2; ++siguiente2;
	//Lit possiguiente2 = siguiente2; ++possiguiente2;	
	
	while (siguiente2 != camino.end()){	
	    // Ubica el tercer punto
	    Lit punto3 = siguiente2;
	    Lit siguiente3 = punto3; ++siguiente3;
	    
	    while (punto3 != camino.end()){
		// Realiza el intercambio si la distancia mejora con el cambio.
		int combinacion_minima = combinacionMejor(problema, camino, punto1, punto2, punto3);
		
		// Realiza el cambio pedido
		if (combinacion_minima != 0){
		    list<int> corte2;
		    list<int> corte3;
		    
		    corte2.splice(corte2.begin(), camino, siguiente1, siguiente3);		    
		    corte3.splice(corte3.begin(), corte2, siguiente2, corte2.end());
		    
		    switch (combinacion_minima){
		    case 1:{
			corte3.reverse();
			camino.splice(siguiente3, corte3);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte2);
		    }; break;

		    case 2: {
			corte2.reverse();
			camino.splice(siguiente3, corte3);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte2);
		    }; break;
			    
		    case 3: {
			corte2.reverse();
			corte3.reverse();
			camino.splice(siguiente3, corte2);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte3);
		    }; break;
			    
		    case 4:{
			camino.splice(siguiente3, corte3);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte2);
		    }; break;

		    case 5:{
			corte2.reverse();
			camino.splice(siguiente3, corte2);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte3);
		    }; break;

		    case 6:{
			corte3.reverse();
			camino.splice(siguiente3, corte2);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte3);
		    }; break;

		    case 7:{
			corte2.reverse();
			corte3.reverse();
			camino.splice(siguiente3, corte3);
			punto2 = siguiente3; --punto2;
			camino.splice(siguiente3, corte2);
		    }; break;
		    }
		    		    
		    continuar = true;
		    punto3 = siguiente3; --punto3;
		    siguiente1 = punto1; ++siguiente1;
		    siguiente2 = punto2; ++siguiente2;
		}

		++punto3;
		++siguiente3;          
	    }

	    ++punto2;
	    ++siguiente2;
	    //possiguiente2 = siguiente2; ++possiguiente2;          
	}
        
	++punto1;
	++siguiente1;
        possiguiente1 = siguiente1; ++possiguiente1;
    }   
}

int H3opt::combinacionMejor (const Problema& problema, list<int>& camino, Lit punto1, Lit punto2, Lit punto3){
    // Coloca los iteradores
    Lit siguiente1 = punto1; ++siguiente1;
    Lit siguiente2 = punto2; ++siguiente2;
    Lit siguiente3 = punto3; ++siguiente3;
    if (siguiente3 == camino.end()) siguiente3 = camino.begin();

    // Realiza el intercambio si la distancia mejora con el cambio.
    double distancia_minima = 
	problema.distancia(*punto1,*siguiente1) 
	+ problema.distancia(*punto2,*siguiente2)
	+ problema.distancia(*punto3,*siguiente3);
    int combinacion_minima = 0;
    double distancia_original = distancia_minima;

    // Consideramos todos los siete casos de mejora posibles en 3opt
    double distancia_nueva;
    // Caso 1
    distancia_nueva =
	problema.distancia(*punto1,*punto3)
	+ problema.distancia(*siguiente1,*siguiente2)
	+ problema.distancia(*punto2,*siguiente3);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 1;
	distancia_minima = distancia_nueva;
    }
    // Caso 2
    distancia_nueva = 
	problema.distancia(*punto1,*siguiente2)
	+ problema.distancia(*punto3,*punto2)
	+ problema.distancia(*siguiente1,*siguiente3);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 2;
	distancia_minima = distancia_nueva;
    }
    // Caso 3
    distancia_nueva = 
	problema.distancia(*punto1,*punto2)
	+ problema.distancia(*siguiente2,*siguiente3)
	+ problema.distancia(*punto3,*siguiente1);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 3;
	distancia_minima = distancia_nueva;
    }
    // Caso 4
    distancia_nueva = 
	problema.distancia(*punto1,*siguiente2)
	+ problema.distancia(*siguiente1,*punto3)
	+ problema.distancia(*siguiente3,*punto2);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 4;
	distancia_minima = distancia_nueva;
    }
    // Caso 5
    distancia_nueva = 
	problema.distancia(*punto1,*punto2)
	+ problema.distancia(*siguiente1,*siguiente2)
	+ problema.distancia(*punto3,*siguiente3);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 5;
	distancia_minima = distancia_nueva;
    }
    // Caso 6
    distancia_nueva = 
	problema.distancia(*punto1,*siguiente1)
	+ problema.distancia(*punto2,*punto3)
	+ problema.distancia(*siguiente2,*siguiente3);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 6;
	distancia_minima = distancia_nueva;
    }	    
    // Caso 7
    distancia_nueva = 
	problema.distancia(*punto1,*punto3)
	+ problema.distancia(*punto2,*siguiente2)
	+ problema.distancia(*siguiente1,*siguiente3);
    if (distancia_nueva < distancia_minima){
	combinacion_minima = 7;
	distancia_minima = distancia_nueva;
    }
    
    // Hay fallos en la comparacion de doubles. La precision es insuficiente.
    // Si no se corrige sumando epsilon, produce modificaciones que no mejoran la distancia.
    if (combinacion_minima != 0)
	if (distancia_original < distancia_minima + 10e-8)
	    combinacion_minima = 0;

    return combinacion_minima;
}
