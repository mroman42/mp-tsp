/**
 * TSP - ioTSP
 * Archivo: ioTSP.cpp
 */

#include"ioTSP.h"
using namespace std;

namespace mensajes {
	const string ERROR_LECTURA = "Fallo en la lectura del archivo.";
    const string ERROR_FORMATO = "Formato del archivo incorrecto.";
    const string CODIGO_CIUDAD = "#Codigo ciudad: ";
    const string COSTE_TOTAL   = "#   Coste Global: ";
}

Problema leeProblema (const string fichero){
    // Abre el archivo
    ifstream archivo;
    archivo.open(fichero.c_str());
    if (!archivo.is_open())
        throw logic_error (mensajes::ERROR_LECTURA);

    // Lee la cabecera del archivo.
    string cabecera;
    int dimension;
    archivo >> cabecera;
    archivo >> dimension;
    if (cabecera != "DIMENSION:")
        throw logic_error (mensajes::ERROR_FORMATO);
    
    // Crea el listado de ciudades. Lee cada ciudad.
    Ciudad* ciudades = new Ciudad[dimension];
    int indice;
    for (int i=0; i<dimension; i++){
        archivo >> indice;
        archivo >> ciudades[i].x;
	archivo >> ciudades[i].y;
    }

    // Genera el problema
    archivo.close();
    return Problema(dimension, ciudades);
}


void muestraSolucion (const Problema& problema, const vector<int>& solucion){
    int dimension = problema.DIMENSION;
    
    // Mostramos las ciudades que componen el camino de forma ordenada. 
    for (int i=0; i<dimension; i++){
	    Ciudad ciudad_actual = problema.ciudad(solucion[i]);
	    cout << ciudad_actual.x << ' ' << ciudad_actual.y<< endl;
    }

    Ciudad ciudad_actual = problema.ciudad(solucion[0]);
    cout << ciudad_actual.x << ' ' << ciudad_actual.y << endl;
}


void muestraRuta (const Problema& problema, const vector<int>& solucion){
    int dimension = problema.DIMENSION;
	
    // Mostramos las ciudades que componen el camino de forma ordenada. 
    for (int i=0; i<dimension; i++)
	    cout << mensajes::CODIGO_CIUDAD << solucion[i]+1 << endl;
    cout << mensajes::CODIGO_CIUDAD << solucion[0]+1 << endl; 
    cout << mensajes::COSTE_TOTAL << problema.coste(solucion) << endl; 
}
