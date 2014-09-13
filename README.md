mp-tsp
======

Práctica sobre el TSP para Metodología de la Programación.  
Se implementan varias heurísticas y algoritmos para la resolución del **TSP**
y se comparan sus tiempos de ejecución, así como la calidad de soluciones obtenidas.

## Modo de uso
El ejecutable `./bin/tsp` puede llamarse sobre cualquier instancia del problema con
el formato dado por las instancias de la carpeta `./instancias`. La heurística que
aplicará se decide por medio de un flag auxiliar al llamar al ejecutable.
```
Heurísticas:
	 '-v' Vecino más cercano             
	 '-f' Fuerza bruta            
	 '-o' Vecino más cercano + 2-OPT            
	 '-s' Segmentos            
	 '-t' Segmentos + 2-OPT            
	 '-p' 2-OPT en bruto            
	 '-3' 3-OPT en bruto            
	 '-i' Inserción sobre triangulo            
	 '-e' Inserción sobre envolvente            
	 '-m' Multi 2-OPT sobre Vecino más cercano            
	 '-w' Vecino más cercano + 3-OPT            
	 '-x' 3-OPT sobre Multi 2-OPT            
	 '-k' Multi 3-OPT sobre Vecino más cercano

```
La salida mostrará primero el orden de los códigos de las ciudades de la ruta óptima,
el coste total de la solución, las coordenadas de las ciudades, y por último, el tiempo
consumido.

Para ejecutar directamente todas las heurísticas posibles sobre todas las instancias de la
carpeta `./instancias`, puede ejecutarse el script `./solvehtml.sh`, que generará además
una tabla html en la que comparar los resultados en tiempo y coste.

## Implementación
### Cálculo del tiempo
Para calcular el tiempo que utiliza cada algoritmo, se usa `chrono::high_resolution_clock`,
de la librería `chorno` de `C++`. El tiempo se mide desde la selección del algoritmo hasta
la escritura de los datos de la solución.
