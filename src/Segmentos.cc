/**
 * TSP - Segmentos
 * Archivo: Segmentos.cpp
 */

#include"Segmentos.h"
typedef list<int>::iterator Lit;
typedef list< list <int> >::iterator LLit;
using namespace std;

vector<int> Segmento::resolver(const Problema& problema){
    int dimension = problema.DIMENSION; 
    list < list <int> > segmentos;
    
    // Crea segmentos unitarios
    for (int i = 0; i < dimension; i++){
        list <int> nueva_lista;
        nueva_lista.push_back(i);   
        segmentos.push_back(nueva_lista);
    }
    
    // Realiza la unión progresiva de segmentos
    unirMasCercanas(segmentos, problema);

    // Devuelve la lista como un vector normal
    list<int> solucion_lista = *segmentos.begin();    
    vector<int> solucion;
    solucion.reserve(dimension);
    for (Lit i = solucion_lista.begin(); i != solucion_lista.end(); ++i)
	solucion.push_back(*i);

    return solucion;
}

void Segmento::unirMasCercanas (list< list<int> >& segmentos, const Problema& problema){
    double distancia_minima;
    bool principio_primera = true;
    bool principio_segunda = true; // Primera referencia a i. Segunda a j. Unimos i a j. 
    LLit minimo_i, minimo_j;

    // Trabajamos hasta que nuestra lista solo contenga un elemento, que será la lista final. 
    while (segmentos.size() != 1){  
        // Inicializamos la distancia a INFINITY. 
        distancia_minima = INFINITY;

        for (LLit i = segmentos.begin(); i != segmentos.end(); ++i){ 
            LLit j = i; ++j;

            while (j != segmentos.end()){
                Lit inicio_i = (*i).begin();
                Lit inicio_j = (*j).begin();
                Lit final_j = (*j).end(); --final_j;
                Lit final_i = (*i).end(); --final_i; 
                    
                // Calculamos la distancia entre los primeros elementos de las dos listas que apuntan los iteradores.
                if (problema.distancia(*inicio_i, *inicio_j) < distancia_minima){
                    distancia_minima = problema.distancia(*inicio_i, *inicio_j);
                    principio_primera = true; principio_segunda = true; 
                    minimo_j = j; minimo_i = i;  
                }
                // Distancia primero - último.
                if (problema.distancia(*inicio_i, *final_j) < distancia_minima){
                    distancia_minima = problema.distancia(*inicio_i, *final_j);
                    principio_primera = true; principio_segunda = false; 
                    minimo_j = j; minimo_i = i;
                }
                // Distancia último - primero.
                if (problema.distancia(*final_i, *inicio_j) < distancia_minima){
                    distancia_minima = problema.distancia(*final_i, *inicio_j);
                    principio_primera = false; principio_segunda = true;  
                    minimo_j = j; minimo_i = i;
                }
                // Distancia último - último. 
                if (problema.distancia(*final_i, *final_j) < distancia_minima){
                    distancia_minima = problema.distancia(*final_i, *final_j);
                    principio_primera = false; principio_segunda = false; 
                    minimo_j = j; minimo_i = i;
                }

		++j;
            }
        }


        // Comprobamos cual es la unión entre las listas, para aplicar el algoritmo necesario. 
        // Unión principio - principio. 
        if (principio_primera && principio_segunda){
            (*minimo_i).reverse(); 
            (*minimo_j).splice((*minimo_j).begin(), *minimo_i);
        } 
        // Unión principio - final.
        else if (principio_primera && !principio_segunda)
            (*minimo_j).splice((*minimo_j).end(), *minimo_i);

        // Unión final - principio. 
        else if (principio_segunda)
            (*minimo_j).splice((*minimo_j).begin(), *minimo_i);

        // Unión final - final. 
        else{
            (*minimo_i).reverse();
            (*minimo_j).splice((*minimo_j).end(), *minimo_i);
        }

        // Eliminamos la lista que ya hemos unido a la otra. 
        segmentos.erase(minimo_i);
    }      
}

