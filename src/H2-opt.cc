/**
 * TSP - 2-OPT
 * Archivo: H2-opt.cpp
 */

#include"H2-opt.h" 
#define SIGUIENTE(a,c) {a++; if(a == c.end()) a = c.begin();}  

using namespace std;
typedef list<int>::iterator Lit;

vector<int> H2opt::resolver(const Problema& problema, const vector<int>& solucion_parcial){
    // Trabajaremos el camino en una lista enlazada
    // Asi hacemos que sea menos costoso computacionalmente rotar partes del camino
    list<int> camino;
    for (int i=0; i<problema.DIMENSION; i++)
	camino.push_back(solucion_parcial[i]);

    // Resolucion
    resolverLista(problema, camino);

    // Devuelve el camino como un array normal
    vector<int> solucion;
    solucion.reserve(problema.DIMENSION);
    for (Lit i = camino.begin(); i != camino.end(); i++)
	solucion.push_back(*i);

    return solucion;
}


void H2opt::resolverLista (const Problema& problema, list<int>& camino){
    // El algoritmo continuara hasta que no haya producido ningun cambio 
    bool continuar = true;

    while (continuar){
	continuar = false;
	Lit actual = camino.begin();
	Lit siguiente = actual; ++siguiente;
	Lit possiguiente = siguiente; ++possiguiente;
	

	while(possiguiente != camino.end() && siguiente != camino.end()){
	    // Fija una pareja de puntos con 'actual' y 'siguiente'
	    // Fija una pareja siguiente con 'otro' y 'sig_otro'
	    // Probará a intercambiar cada una de estas parejas
	    Lit otro = possiguiente;
	    Lit sig_otro = otro; ++sig_otro;
	    bool hay_cambios = false;

	    // Recorre el camino probando intercambios
	    while(otro != camino.end() && !hay_cambios){
		if (sig_otro == camino.end()) sig_otro = camino.begin();
		
		// Realiza el intercambio si la distancia mejora con el cambio.
		double distancia_actual = problema.distancia(*actual,*siguiente) 
		    + problema.distancia(*otro, *sig_otro);
		double distancia_nueva = problema.distancia(*actual,*otro)
		    + problema.distancia(*siguiente,*sig_otro);
		
		if (distancia_nueva < distancia_actual){
		    // Rota la zona intermedia entre los puntos
		    list<int> corte;
		    corte.splice(corte.begin(), camino, siguiente, otro);
		    corte.reverse();
		    camino.splice(sig_otro, corte, corte.begin(), corte.end());
		    
		    // Recoloca los iteradores
		    siguiente = actual; SIGUIENTE(siguiente, camino);
		    otro = sig_otro; --otro;
		    hay_cambios = true;
		    continuar = true;
		}
		
		++otro;
		++sig_otro;
	    }
	    
	    ++actual;
	    ++siguiente;
	    possiguiente = siguiente; ++possiguiente;
	}
    }
}
