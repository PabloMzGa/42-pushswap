#!/bin/bash

# Verificar si se proporcionaron los argumentos correctos
if [ $# -ne 4 ]; then
    echo "Uso: $0 <repeticiones> <cantidad> <min> <max>"
    echo "  repeticiones: Número de veces que se ejecutará la prueba"
    echo "  cantidad: Número de valores aleatorios a generar"
    echo "  min: Valor mínimo del rango"
    echo "  max: Valor máximo del rango"
    exit 1
fi

repeticiones=$1
cantidad=$2
min=$3
max=$4

# Validar entradas
if ! [[ "$repeticiones" =~ ^[0-9]+$ ]]; then
    echo "Error: Las repeticiones deben ser un número entero positivo"
    exit 1
fi
if ! [[ "$cantidad" =~ ^[0-9]+$ ]]; then
    echo "Error: La cantidad debe ser un número entero positivo"
    exit 1
fi
if ! [[ "$min" =~ ^-?[0-9]+$ ]]; then
    echo "Error: El mínimo debe ser un número entero"
    exit 1
fi
if ! [[ "$max" =~ ^-?[0-9]+$ ]]; then
    echo "Error: El máximo debe ser un número entero"
    exit 1
fi
if [ "$min" -gt "$max" ]; then
    echo "Error: El mínimo debe ser menor o igual que el máximo"
    exit 1
fi

# Escribir cabecera de parámetros en results y limpiar archivos
{
    echo "Parametros: repeticiones=$repeticiones cantidad=$cantidad min=$min max=$max"
} > results
echo "" > max_case.txt

# Crear archivo para casos que superan 5500 movimientos si no existe
if [ ! -f cases_over_5500.txt ]; then
    {
        echo "=== CASOS QUE SUPERAN 5500 MOVIMIENTOS ==="
        echo "Archivo creado: $(date)"
        echo "============================================"
    } > cases_over_5500.txt
fi

# Añadir nueva sesión al archivo de casos que superan 5500 movimientos
{
    echo ""
    echo "=== NUEVA SESIÓN DE PRUEBAS ==="
    echo "Fecha: $(date)"
    echo "Parametros: repeticiones=$repeticiones cantidad=$cantidad min=$min max=$max"
    echo "================================="
    echo ""
} >> cases_over_5500.txt

echo "Ejecutando $repeticiones pruebas..."

for ((r=1; r<=repeticiones; r++)); do
    # Calcular el tamaño del rango
    rango=$((max - min + 1))

    # Verificar que la cantidad no exceda el rango disponible
    if [ "$cantidad" -gt "$rango" ]; then
        echo "Error: No se pueden generar $cantidad números únicos en el rango $min-$max" >&2
        exit 1
    fi

    # Crear un array con todos los números en el rango
    declare -a numeros
    for ((i=min; i<=max; i++)); do
        numeros+=($i)
    done

    # Mezclar el array (algoritmo Fisher-Yates)
    for ((i=rango-1; i>0; i--)); do
        j=$((RANDOM % (i+1)))
        # Intercambiar elementos
        temp=${numeros[i]}
        numeros[i]=${numeros[j]}
        numeros[j]=$temp
    done

    # Crear un string con los números generados
    NUMS=""
    for ((i=0; i<cantidad; i++)); do
        NUMS+="${numeros[i]} "
    done

    # Ejecutar push_swap con los números y capturar la salida
    PUSH_SWAP_OUTPUT=$(./push_swap $NUMS)
    LINE_COUNT=$(echo "$PUSH_SWAP_OUTPUT" | wc -l)
    echo "$LINE_COUNT" >> results

    # Si supera 5500 operaciones, guardar el caso completo con todos los movimientos
    if [ "$LINE_COUNT" -gt 5500 ]; then
        echo "--- CASO #$r ---" >> cases_over_5500.txt
        echo "OPERACIONES: $LINE_COUNT" >> cases_over_5500.txt
        echo "SECUENCIA: $NUMS" >> cases_over_5500.txt
        echo "./push_swap $NUMS" >> cases_over_5500.txt
        echo "" >> cases_over_5500.txt
        echo "MOVIMIENTOS EJECUTADOS:" >> cases_over_5500.txt

        # Formatear los movimientos: espacios en lugar de saltos de línea, 100 por línea
        FORMATTED_MOVES=""
        MOVE_COUNT=0
        while IFS= read -r move; do
            if [ -n "$move" ]; then
                MOVE_COUNT=$((MOVE_COUNT + 1))
                if [ $MOVE_COUNT -eq 1 ]; then
                    FORMATTED_MOVES="$move"
                else
                    FORMATTED_MOVES="$FORMATTED_MOVES $move"
                fi

                # Cada 100 movimientos, hacer salto de línea
                if [ $((MOVE_COUNT % 100)) -eq 0 ]; then
                    echo "$FORMATTED_MOVES" >> cases_over_5500.txt
                    FORMATTED_MOVES=""
                    MOVE_COUNT=0
                fi
            fi
        done <<< "$PUSH_SWAP_OUTPUT"

        # Escribir los movimientos restantes si los hay
        if [ -n "$FORMATTED_MOVES" ]; then
            echo "$FORMATTED_MOVES" >> cases_over_5500.txt
        fi

        echo "" >> cases_over_5500.txt
        echo "--- FIN DEL CASO #$r ---" >> cases_over_5500.txt
        echo "" >> cases_over_5500.txt
    fi

    # Guardar el caso y sus números en un archivo temporal
    echo "$LINE_COUNT:$NUMS" >> results_cases_tmp

done

echo "Pruebas completadas."

# Mostrar progreso de casos que superan 5500
if [ -f cases_over_5500.txt ] && [ -s cases_over_5500.txt ]; then
    CASES_COUNT=$(grep -c "--- CASO #" cases_over_5500.txt)
    SESSIONS_COUNT=$(grep -c "=== NUEVA SESIÓN DE PRUEBAS ===" cases_over_5500.txt)
    echo "Se encontraron $CASES_COUNT casos que superan 5500 operaciones en esta sesión"
    echo "Total de sesiones registradas: $SESSIONS_COUNT"
    echo "Casos acumulados guardados en: cases_over_5500.txt"
    echo "Para revisar todos los casos: cat cases_over_5500.txt"
else
    echo "No se encontraron casos que superen 5500 operaciones en esta sesión"
fi

# Buscar el caso con más movimientos y guardar sus números en max_case.txt
if [ -f results_cases_tmp ]; then
    MAX_MOV=0
    MAX_NUMS=""
    while IFS=: read -r mov nums; do
        if [[ $mov =~ ^[0-9]+$ ]]; then
            if [ $mov -gt $MAX_MOV ]; then
                MAX_MOV=$mov
                MAX_NUMS=$nums
            fi
        fi
    done < results_cases_tmp
    if [ -n "$MAX_NUMS" ]; then
        echo "$MAX_NUMS" > max_case.txt
    fi
    rm results_cases_tmp
fi

# Calcular la media, el máximo, el mínimo y cuántos casos superan los 5500 movimientos, y escribirlos al principio de results
if [ -s results ]; then
    SUM=0
    COUNT=0
    MAX=0
    MIN=0
    FIRST=1
    OVER_5500=0
    while IFS= read -r line; do
        if [[ $line =~ ^[0-9]+$ ]]; then
            SUM=$((SUM + line))
            COUNT=$((COUNT + 1))
            if [ $FIRST -eq 1 ]; then
                MAX=$line
                MIN=$line
                FIRST=0
            else
                if [ $line -gt $MAX ]; then
                    MAX=$line
                fi
                if [ $line -lt $MIN ]; then
                    MIN=$line
                fi
            fi
            if [ $line -gt 5500 ]; then
                OVER_5500=$((OVER_5500 + 1))
            fi
        fi
    done < <(tail -n +2 results)
    if [ $COUNT -gt 0 ]; then
        MEDIA=$(awk "BEGIN {printf \"%.2f\", $SUM/$COUNT}")
        sed -i "1iCasos que superan 5500 operaciones: $OVER_5500" results
        sed -i "1iValor máximo de operaciones: $MAX" results
        sed -i "1iValor mínimo de operaciones: $MIN" results
        sed -i "1iMedia de operaciones: $MEDIA" results
    fi
fi
