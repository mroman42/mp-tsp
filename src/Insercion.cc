/**
 * TSP - Insercion
 * Archivo: Insercion.cpp
 */

#include "Insercion.h"
#define ANTERIOR(a,c) {if(a==c.begin()) a=c.end(); --a;}  
using namespace std;
typedef list<int>::iterator Lit;
typedef vector<int>::iterator Vit;

list<int> Insercion::crearTriangulo (const Problema& problema, vector<bool>& usadas){
    // Buscamos las ciudades del triangulo segun coordenadas
    Ciudad actual = problema.ciudad(0);
    int arriba    = 0; // Ciudad de arriba
    int derecha   = 0; // Ciudad a la derecha
    int izquierda = 0; // Ciudad a la izquierda
    double y_arriba    = actual.y;
    double x_derecha   = actual.x;
    double x_izquierda = actual.x;

    // Si puede ser mejorada, se almacena la ciudad
    int dimension = problema.DIMENSION;
    for (int i=1; i<dimension; i++){
	actual = problema.ciudad(i);
	double x = actual.x;
	double y = actual.y;

	if (x > x_derecha){
	    derecha = i;
	    x_derecha = x;
	} else if (x < x_izquierda){
	    izquierda = i;
	    x_izquierda = x;
	}

	if (y > y_arriba){
	    arriba = i;
	    y_arriba = y;
	}
    }
    
    // Se construye el triangulo
    // Siempre que no haya puntos repetidos
    list<int> triangulo;
    triangulo.push_back(arriba);
    usadas[arriba]    = true;
    if (izquierda != arriba){
	triangulo.push_back(izquierda);
	usadas[izquierda] = true;
	if (derecha != izquierda && derecha != arriba){
	    triangulo.push_back(derecha);
	    usadas[derecha]   = true;
	}
    }

    return triangulo;
}


double Insercion::giro (const int i1, const int i2, const int i3, const Problema& problema){
    // Devolverá positivo si el giro es contra las agujas del reloj.
    // Devolverá negativo si el giro es con las agujas del reloj.
    // Devuelve 0 con puntos colineales.
    const Ciudad a = (problema.ciudad(i1));
    const Ciudad b = (problema.ciudad(i2));
    const Ciudad c = (problema.ciudad(i3));

    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

bool Insercion::angulo_menor (const int indice1, const int indice2, const Problema& problema, const int primera_ciudad){
    // Tangente de la primera ciudad
    double tan1 = (problema.ciudad(indice1).y - problema.ciudad(primera_ciudad).y) /
	(problema.ciudad(indice1).x - problema.ciudad(primera_ciudad).x);
    // Tangente de la segunda ciudad
    double tan2 = (problema.ciudad(indice2).y - problema.ciudad(primera_ciudad).y) /
	(problema.ciudad(indice2).x - problema.ciudad(primera_ciudad).x);

    return (tan1 <= tan2);
}

list<int> Insercion::crearEnvolvente (const Problema& problema, vector<bool>& usadas){
    // Usaremos el algoritmo del Método de Graham
    // http://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham

    int dimension = problema.DIMENSION;

    // 1. Buscamos el punto inicial como el punto más a la derecha
    int ciudad_inicial = 0;    
    double x_minima = INFINITY;
    for (int i=0; i<dimension; i++){
	double x_actual = problema.ciudad(i).x;
        if (x_actual < x_minima){
	    ciudad_inicial = i;
	    x_minima = x_actual;
	}
    }

    // 2. Tomamos todas las ciudades, y colocamos la primera al principio y al final  
    vector<int> ciudades;
    ciudades.reserve(dimension);
    for (int i=0; i<dimension; i++)
        ciudades.push_back(i);

    ciudades[0] = ciudad_inicial;
    ciudades[ciudad_inicial] = 0;

    // 3. Ordenamos las ciudades en función del ángulo a la primera
    Vit inicio = ciudades.begin(); ++inicio;     
    sort(inicio, ciudades.end(), // Usamos notación lambda (C++11)
	 [ciudad_inicial, &problema, this](int i1, int i2){return this->angulo_menor(i1,i2,problema,ciudad_inicial);}
	);

    // 4. Excluimos los puntos en la envolvente que creen giros a la derecha
    stack<int> envolvente;
    envolvente.push(ciudades[0]);
    envolvente.push(ciudades[1]);

    for (int i=2; i<dimension; i++){
	// Si hay menos de dos puntos, introducimos el siguiente
	if (envolvente.size() < 2){
	    envolvente.push(i);
	} else {
	    int intermedio = envolvente.top();

	    envolvente.pop();
	    
	    // Eliminamos los giros a derecha
	    while (giro(envolvente.top(), intermedio, ciudades[i], problema) < 0){
		intermedio = envolvente.top();
		envolvente.pop();
	    }

	    envolvente.push(intermedio);
	    envolvente.push(ciudades[i]);
	}
    }

    // 5. Devolvemos la envolvente como una lista
    list<int> envolvente_final; 
    while (!envolvente.empty()){
	envolvente_final.push_front(envolvente.top());
	usadas[envolvente.top()] = true;
	envolvente.pop();
    }

    return envolvente_final;
}




vector<int> Insercion::resolver(const Problema& problema, bool envolvente){
    int dimension = problema.DIMENSION;

    // Inicializa las ciudades usadas
    vector<bool> usadas;
    usadas.reserve(dimension);
    for (int i=0; i<dimension; i++)
	usadas.push_back(false);

    // Crea el camino inicial
    list<int> camino;
    if (envolvente)
        camino = crearEnvolvente(problema, usadas);
    else
        camino = crearTriangulo (problema, usadas);    
    int tamanio = camino.size();

    // Une las ciudades de insercion mas economica al camino
    while (tamanio < dimension){
	int ciudad_minima = 0;
	Lit posicion_minima = camino.begin();
	double coste_minimo = INFINITY;

	// Busca entre todas las ciudades posibles
	for (int j=0; j<dimension; j++){
	    if (!usadas[j]){
		// Busca entre todos los puntos de insercion posibles
		for (Lit k = camino.begin(); k != camino.end(); ++k){
		    Lit anterior = k; ANTERIOR(anterior,camino);
		    double coste_actual = 
			  problema.distancia (*k,j) 
			+ problema.distancia (*anterior,j) 
			- problema.distancia (*k,*anterior);

		    if (coste_actual < coste_minimo){
			ciudad_minima = j;
			posicion_minima = k;
			coste_minimo = coste_actual;
		    }
		}
	    }
	}

	// Inserta la mejor
	camino.insert(posicion_minima, ciudad_minima);
	usadas[ciudad_minima] = true;
	++tamanio;
    }

    // Traslada la solucion a un vector
    vector<int> solucion;
    solucion.reserve(problema.DIMENSION);
    for (Lit i=camino.begin(); i != camino.end(); ++i)
	solucion.push_back(*i);
    
    return solucion;
}
