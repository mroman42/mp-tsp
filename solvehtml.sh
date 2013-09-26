#!/bin/bash
# Solveall
# Version 1

##
# Este script resuelve todos los circuitos de la carpeta de instancias 
# y muestra el coste y tiempo de cada heuristica.
# 
# Presenta una tabla con los datos de heuristica-tiempo-distancia.
# La salida se vierte en solveall.html.
##

# Lista de heuristicas
NUM_HEUR=13 #Numero de heuristicas
HEURISTICAS=(VMC  VMC-2opt  Fuerza 2opt  Segmentos Seg-2opt Insercion Envolvente Multi2opt 3opt VMC-3opt Multi2+3opt Multi3opt X)
FLAGS=(      -v   -o        -f     -p    -s        -t       -i        -e         -m        -3   -w       -x          -k         )
LIMITE=(     1005 1005       11   10000  1005      1005     1005      1005       500       500  500      500        110        )

##########################
# EXTRACCION DE DATOS
##########################
{

#awk 'match($0,"[a-zA-Z]+"){printf substr($0,RSTART,RLENGTH)} match($0,"[0-9]+"){printf substr($0,RSTART,RLENGTH)}'
# Resolucion para cada instancia
for INSTANCIA in `ls ./instancias/*.tsp | cut -f3 -d'/' | cut -f1 -d'.' | awk 'match($0,"[0-9]+"){printf substr($0,RSTART,RLENGTH)} match($0,"[a-zA-Z]+"){print substr($0,RSTART,RLENGTH)}' | sort -V | awk 'match($0,"[a-zA-Z]+"){printf substr($0,RSTART,RLENGTH)} match($0,"[0-9]+"){print substr($0,RSTART,RLENGTH)}'`

do
    INSTANCIA="./instancias/$INSTANCIA.tsp"
    let CIUDADES=`head $INSTANCIA -n1 | cut -f2 -d' '`
    NOMBRE=${INSTANCIA##*/}
    NOMBRE=${NOMBRE%.tsp}
    echo -e "$NOMBRE"
    
    # Resolucion para cada heuristica
    for ((i=0; i < $NUM_HEUR; i++)) 
    do 
        if (( $CIUDADES < ${LIMITE[i]})); then
            echo "${HEURISTICAS[i]} - $INSTANCIA" 1>&2
        
            OUTPUT=`./bin/tsp $INSTANCIA ${FLAGS[i]} | grep "Coste Global\|Tiempo total"`  
            TIEMPO=`echo $OUTPUT | rev | cut -f2 -d' ' | rev`
            TIEMPO=$(awk -vinput="$TIEMPO" 'BEGIN{printf "%.8f", input }')
            COSTE=`echo $OUTPUT | cut -f4 -d' '`
        else
            TIEMPO="X"
            COSTE="X"
        fi
        
        echo "$NOMBRE:${HEURISTICAS[i]}:$COSTE:$TIEMPO"
    done
done

} > data.solveall



###############################
# Presentacion de los datos
###############################

# Cabecera del HTML
{ 
    printf "
        <!DOCTYPE html>
        <html>
        <!-------- Html generado por solvehtml.sh ---------->
        <head>
          <title>Prueba</title>
        </head>


        <body><FONT face=\"Verdana, Computer Modern\">
          <center>
          <h1>Resoluci&#243n del TSP.</h1>
          <hr></hr>
    "

# Cabecera de tabla de Costes
printf "
     <center><h2>Tabla de costes</h2></center>
     <table border=1>
        <col style=\"width:150px\" />
"

cat data.solveall | {
#COSTES
    # Cabecera
    printf '
        <tr>
	<th scope="col">Instancias</th>
    '
    for ((i=0; i < $NUM_HEUR; i++)) 
    do 
        printf '<th scope="col" width=100px>' 
	printf "${HEURISTICAS[i]}</th>" 
    done
    printf '</tr>'
    

    # Instancias
    while read Instancia
    do
	printf "<tr><td><center> $Instancia </center></td>"
        for ((i=0; i < $NUM_HEUR; i++)) 
        do
            read linea
            coste=`echo $linea | cut -f3 -d':'`
            printf "<td align=center> $coste </td>"
        done
    done
}

#Fin de la tabla de costes
printf "
    </table><hr></hr>
"



# Cabecera de tabla de Tiempos
printf "
     <center><h2>Tabla de tiempos</h2></center>
     <table>
        <table border=\"1\" align=\"center\">
        <col style=\"width:150px\" />
"


cat data.solveall | {
#TIEMPO
    # Cabecera
    printf '
        <tr>
	<th scope="col">Instancias</th>
    '
    for ((i=0; i < $NUM_HEUR; i++)) 
    do 
        printf '<th scope="col" width=100px>' 
	printf "${HEURISTICAS[i]}</th>" 
    done
    printf '</tr>'

    # Instancias
    while read Instancia
    do
        printf "<tr><td><center> $Instancia </center></td>"
        for ((i=0; i < $NUM_HEUR; i++)) 
        do
            read linea
            tiempo=`echo $linea | cut -f4 -d':'`
            printf "<td><center> $tiempo </center></td>"
        done
    done
}

#Fin de la tabla de tiempos
printf "
    </table><hr></hr>
"

#Segunda seccion: tablas particulares


cat data.solveall | {
    # Cabecera de tabla de costes medios
    printf "
     <center><h2>Costes Medios</h2></center>
     <table>
        <table border="1">
        <col style=\"width:150px\" />
    "
    #COSTE MEDIO
    printf '
        <tr>
	<th scope="col" width=100px>Costes</th>
        <th scope="col" width=100px>Minimo</th>
        <th scope="col" width=100px>Heuristica</th>
        <th scope="col" width=100px>Medio</th>
        </tr>
    '

    while read Instancia
    do
        let media=0
        let HEUR_usadas=$NUM_HEUR
        heur_min=$NUM_HEUR
        minimo="X"

        printf "<tr> <td> <center> $Instancia </center> </td>" 
        for ((i=0; i < $NUM_HEUR; i++)) 
        do
            read linea
            coste=`echo $linea | cut -f3 -d':'`           

            if [ "$coste" != "X" ]; then
                media=`echo "$media+$coste" | bc -l`
                ( [[ $minimo = "X" ]] || [[ `echo "$coste<$minimo" | bc` = "1" ]] ) && minimo=$coste && heur_min=$i;
            else
                let HEUR_usadas--
            fi           
        done

        if [ $HEUR_usadas -eq 0 ]; then
            media="X"
        else
            media=`echo "scale=3; $media/$HEUR_usadas" | bc `
        fi

        printf " <td><center> %s </center></td>
                 <td><center> %s </center></td>
                 <td><center> %s </center></td>" $minimo ${HEURISTICAS[$heur_min]} $media 
    done

    #Fin de tabla de costes medios
    printf "</tr></table>"
}

cat data.solveall | {
    # Cabecera de tabla de tiempos medios
    printf "
     <center><h2>Tiempos Medios</h2></center>
     <table>
        <table border="1">
        <col style=\"width:150px\" />
    "

    #TIEMPO MEDIO
    printf '
        <tr>
	<th scope="col" width=100px>Tiempos</th>
        <th scope="col" width=200px>Tiempo Medio</th>
        </tr>
    '
    
    while read Instancia
    do
        let media=0
        let HEUR_usadas=$NUM_HEUR

        printf "<tr><td><center> %s </center></td>" $Instancia
        for ((i=0; i < $NUM_HEUR; i++))
        do
            read linea
            coste=`echo $linea | cut -f4 -d':'`           

            if [ "$coste" != "X" ]; then
                media=`echo "$media+$coste" | bc -l`
            else
                let HEUR_usadas--
            fi           
        done

        if [ $HEUR_usadas -eq 0 ]; then
            media="X"
        else
            media=`echo "scale=15; $media/$HEUR_usadas" | bc `
        fi
        printf " <td align=right> %s </td></tr>" $media
    done
    #Fin de tabla de tiempos medios
    printf "</table>"

}

printf "</FONT></body></html>"
} > Resolucion.html
