#!/bin/bash
# resolver.sh
# Versión 2
#
# Este script de bash ejecuta el programa sobre una instancia del TSP,
# generando los ficheros .data, .ruta y .jpeg asociados a la solución.
# Está preparado para funcionar sobre la ubicación:
# ./instancias/resolver.sh
# Y siempre junto a "script.gnup"
#
# USO: resolver.sh <instancia> <heuristica>
# Ejemplo: ./resolver.sh berlin52 -v
#

# Consulta que exista el archivo que se usará.
if [ ! -f "$1.tsp" ]; then
    echo "No existe el fichero de datos."
    exit
fi;



# Consulta la heurística que se usará.
case "$2" in
-v) HEURISTICA="VMC" ;;
-f) HEURISTICA="Fuerza" ;;
-p) HEURISTICA="2OPT" ;;
-3) HEURISTICA="3OPT" ;;
-o) HEURISTICA="VMC-2OPT" ;;
-i) HEURISTICA="Insert" ;;
-s) HEURISTICA="Segmentos" ;;
-e) HEURISTICA="Envolvente" ;;
-t) HEURISTICA="Segmentos2OPT" ;;
-m) HEURISTICA="Multi-2opt" ;;
-w) HEURISTICA="VMC-3opt" ;;
-x) HEURISTICA="Multi2+3opt" ;;
-k) HEURISTICA="Multi3opt" ;;
*) echo "Heurística incorrecta. Use:"
   echo "Vecino más cercano: -v"
   echo "Fuerza Bruta: -f"
   echo "OPT2 en bruto: -p"
   echo "OPT3 en bruto: -3"
   echo "Vecino más cercano mejorado con OPT2: -o"
   echo "Insercion mas economica: -i"
   echo "Unión de segmentos: -s"
   echo "Unión de segmentos mejorada con OPT2: -t"
   echo "Insercion mejorada con envolvente convexa: -e"
   echo "Multi 2-opt sobre VMC: -m"
   echo "Vecino más cercano mejorado con OPT3: -w"
   echo "Multi 2-opt mejorado con OPT3: -x"
   echo "Multi 3-opt sobre VMC: -k"
   exit ;;
esac



# Crea la carpeta donde guardará la solución y sus archivos
SOLUCION="./"$HEURISTICA"_"$1
if [ ! -d $SOLUCION ]; then
    mkdir $SOLUCION
fi;
echo "#RUTA:" > "$SOLUCION/$1.ruta"
echo "#DATA:" > "$SOLUCION/$1.data"



# Reparte la salida completa del programa entre los dos archivos
{
../bin/tsp "$1.tsp" $2 | while read linea ;
do 
    echo $linea
    
    if [ ${linea:0:1} = "#" ];
    then
        echo ${linea:1} >> "$SOLUCION/$1.ruta"
    else
        echo $linea >> "$SOLUCION/$1.data"
    fi;
done
} && cd $SOLUCION && gnuplot -e "basename='$1'" ../script.gnup && echo "Resuelto correctamente."

#Muestra tiempo y coste totales
tail $1.ruta -n2
xdg-open $1.png &> /dev/null
cd ../
