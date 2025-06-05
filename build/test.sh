#!/bin/bash

# =============================================================================
# SCRIPT DE PRUEBAS PARA PUSH_SWAP
# =============================================================================
# Ejecuta múltiples pruebas del algoritmo push_swap en paralelo y genera
# estadísticas detalladas sobre el rendimiento.
# =============================================================================

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Función para mostrar mensajes con colores
print_header() {
    echo -e "${CYAN}${BOLD}$1${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

# Banner inicial
print_banner() {
    echo -e "${CYAN}${BOLD}"
    echo "═══════════════════════════════════════════════════════════"
    echo "           PUSH_SWAP PERFORMANCE TESTER v2.0"
    echo "═══════════════════════════════════════════════════════════"
    echo -e "${NC}"
}

# Verificar si se proporcionaron los argumentos correctos
if [ $# -ne 4 ]; then
    print_banner
    print_error "Argumentos incorrectos"
    echo -e "${WHITE}Uso:${NC} $0 <repeticiones> <cantidad> <min> <max>"
    echo ""
    echo -e "${BOLD}Parámetros:${NC}"
    echo -e "  ${CYAN}repeticiones${NC}: Número de veces que se ejecutará la prueba"
    echo -e "  ${CYAN}cantidad${NC}:     Número de valores aleatorios a generar"
    echo -e "  ${CYAN}min${NC}:          Valor mínimo del rango"
    echo -e "  ${CYAN}max${NC}:          Valor máximo del rango"
    echo ""
    echo -e "${BOLD}Ejemplo:${NC}"
    echo -e "  ${GREEN}$0 1000 500 1 500${NC}"
    echo ""
    exit 1
fi

repeticiones=$1
cantidad=$2
min=$3
max=$4

print_banner

# Obtener número de núcleos disponibles
MAX_JOBS=${MAX_JOBS:-$(nproc)}
print_info "CPU detectada: $(nproc) núcleos (usando $MAX_JOBS trabajos paralelos)"

# Validar entradas
print_header "🔍 Validando parámetros..."
if ! [[ "$repeticiones" =~ ^[0-9]+$ ]]; then
    print_error "Las repeticiones deben ser un número entero positivo"
    exit 1
fi
if ! [[ "$cantidad" =~ ^[0-9]+$ ]]; then
    print_error "La cantidad debe ser un número entero positivo"
    exit 1
fi
if ! [[ "$min" =~ ^-?[0-9]+$ ]]; then
    print_error "El mínimo debe ser un número entero"
    exit 1
fi
if ! [[ "$max" =~ ^-?[0-9]+$ ]]; then
    print_error "El máximo debe ser un número entero"
    exit 1
fi
if [ "$min" -gt "$max" ]; then
    print_error "El mínimo debe ser menor o igual que el máximo"
    exit 1
fi

# Verificar que push_swap existe
if [ ! -f "./push_swap" ]; then
    print_error "El ejecutable './push_swap' no se encuentra en el directorio actual"
    exit 1
fi

print_success "Parámetros validados correctamente"

# Mostrar configuración
echo ""
print_header "📋 Configuración de la prueba:"
echo -e "  ${BOLD}Repeticiones:${NC} ${MAGENTA}$repeticiones${NC}"
echo -e "  ${BOLD}Cantidad de números:${NC} ${MAGENTA}$cantidad${NC}"
echo -e "  ${BOLD}Rango:${NC} ${MAGENTA}$min${NC} a ${MAGENTA}$max${NC}"
echo -e "  ${BOLD}Trabajos paralelos:${NC} ${MAGENTA}$MAX_JOBS${NC}"

# Calcular tiempo estimado (muy aproximado)
tiempo_estimado=$((repeticiones / MAX_JOBS / 10))
if [ $tiempo_estimado -eq 0 ]; then
    tiempo_estimado="<1"
fi
echo -e "  ${BOLD}Tiempo estimado:${NC} ${MAGENTA}~${tiempo_estimado} minutos${NC}"
echo ""

# Inicializar archivos de resultados
TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
TEMP_DIR="temp_${TIMESTAMP}"
RESULTS_FILE="results_${TIMESTAMP}.txt"
MAX_CASE_FILE="max_case_${TIMESTAMP}.txt"
OVER_5500_FILE="cases_over_5500.txt"

print_header "📁 Preparando archivos de resultados..."

# Crear directorio temporal
if ! mkdir -p "$TEMP_DIR"; then
    print_error "No se pudo crear el directorio temporal: $TEMP_DIR"
    exit 1
fi
print_success "Directorio temporal creado: $TEMP_DIR"

# Crear cabecera detallada en results
{
    echo "═══════════════════════════════════════════════════════════"
    echo "RESULTADOS DE PRUEBAS PUSH_SWAP"
    echo "═══════════════════════════════════════════════════════════"
    echo "Fecha y hora: $(date)"
    echo "Parámetros: repeticiones=$repeticiones cantidad=$cantidad min=$min max=$max"
    echo "Núcleos utilizados: $MAX_JOBS"
    echo "═══════════════════════════════════════════════════════════"
    echo ""
} > "$RESULTS_FILE"

# Limpiar max_case
echo "" > "$MAX_CASE_FILE"

# Crear archivo para casos que superan 5500 movimientos si no existe
if [ ! -f "$OVER_5500_FILE" ]; then
    {
        echo "═══════════════════════════════════════════════════════════"
        echo "           CASOS QUE SUPERAN 5500 MOVIMIENTOS"
        echo "═══════════════════════════════════════════════════════════"
        echo "Archivo creado: $(date)"
        echo "═══════════════════════════════════════════════════════════"
    } > "$OVER_5500_FILE"
fi

# Añadir nueva sesión al archivo de casos que superan 5500 movimientos
{
    echo ""
    echo "╔══════════════════════════════════════════════════════════╗"
    echo "║                  NUEVA SESIÓN DE PRUEBAS                ║"
    echo "╚══════════════════════════════════════════════════════════╝"
    echo "Fecha: $(date)"
    echo "Parámetros: repeticiones=$repeticiones cantidad=$cantidad min=$min max=$max"
    echo "════════════════════════════════════════════════════════════"
    echo ""
} >> "$OVER_5500_FILE"

print_success "Archivos preparados: $RESULTS_FILE, $MAX_CASE_FILE"

# Función para mostrar la barra de progreso mejorada
mostrar_progreso() {
    local completadas=$1
    local total=$2
    local tiempo_transcurrido=$3
    local casos_5500=$4

    local porcentaje=0
    if [ $total -gt 0 ]; then
        porcentaje=$((completadas * 100 / total))
    fi

    local barras_completas=$((porcentaje / 2))
    local barra=""

    # Crear la barra visual con colores
    for ((i=0; i<barras_completas; i++)); do
        barra+="█"
    done
    for ((i=barras_completas; i<50; i++)); do
        barra+="░"
    done

    # Calcular tiempo restante estimado
    local tiempo_restante="--"
    if [ $completadas -gt 0 ] && [ $tiempo_transcurrido -gt 0 ]; then
        local promedio_por_caso=$((tiempo_transcurrido / completadas))
        local casos_restantes=$((total - completadas))
        tiempo_restante=$((promedio_por_caso * casos_restantes))
        if [ $tiempo_restante -gt 60 ]; then
            tiempo_restante="$((tiempo_restante / 60))m $((tiempo_restante % 60))s"
        else
            tiempo_restante="${tiempo_restante}s"
        fi
    fi

    # Mostrar la barra con información detallada
    printf "\r${CYAN}[${GREEN}%s${CYAN}]${NC} ${BOLD}%3d%%${NC} ${MAGENTA}(%d/%d)${NC} │ ${YELLOW}%s${NC} restante │ ${RED}%d${NC} >5500" \
           "$barra" "$porcentaje" "$completadas" "$total" "$tiempo_restante" "$casos_5500"
}

# Función para mostrar estadísticas en tiempo real
mostrar_stats_tiempo_real() {
    local completadas=$1
    if [ $completadas -eq 0 ]; then
        return
    fi

    # Calcular estadísticas rápidas de los archivos temporales
    local suma=0
    local count=0
    local max_temp=0
    local min_temp=999999

    for file in "$TEMP_DIR"/results_tmp_*; do
        if [ -f "$file" ]; then
            while read -r line; do
                if [[ $line =~ ^[0-9]+$ ]]; then
                    suma=$((suma + line))
                    count=$((count + 1))
                    if [ $line -gt $max_temp ]; then
                        max_temp=$line
                    fi
                    if [ $line -lt $min_temp ]; then
                        min_temp=$line
                    fi
                fi
            done < "$file"
        fi
    done

    if [ $count -gt 0 ]; then
        local media=$((suma / count))
        # Limpiar la línea actual y mostrar estadísticas
        printf "\r%*s\r" 100 ""  # Limpiar línea
        echo -e "${BOLD}Stats parciales:${NC} Media=${CYAN}$media${NC} Max=${RED}$max_temp${NC} Min=${GREEN}$min_temp${NC}"
    fi
}

# Función para ejecutar una prueba individual
ejecutar_prueba() {
    local r=$1
    local cantidad=$2
    local min=$3
    local max=$4

    # Calcular el tamaño del rango
    local rango=$((max - min + 1))

    # Verificar que la cantidad no exceda el rango disponible
    if [ "$cantidad" -gt "$rango" ]; then
        echo "Error: No se pueden generar $cantidad números únicos en el rango $min-$max" >&2
        return 1
    fi

    # Crear un array con todos los números en el rango
    local -a numeros
    for ((i=min; i<=max; i++)); do
        numeros+=($i)
    done

    # Mezclar el array (algoritmo Fisher-Yates)
    for ((i=rango-1; i>0; i--)); do
        j=$((RANDOM % (i+1)))
        # Intercambiar elementos
        local temp=${numeros[i]}
        numeros[i]=${numeros[j]}
        numeros[j]=$temp
    done

    # Crear un string con los números generados
    local NUMS=""
    for ((i=0; i<cantidad; i++)); do
        NUMS+="${numeros[i]} "
    done

    # Ejecutar push_swap con los números y capturar la salida
    local PUSH_SWAP_OUTPUT=$(./push_swap $NUMS 2>/dev/null)
    local LINE_COUNT=$(echo "$PUSH_SWAP_OUTPUT" | wc -l)

    # Verificar si hay líneas vacías al final y ajustar
    if [ -n "$PUSH_SWAP_OUTPUT" ] && [ "$(echo "$PUSH_SWAP_OUTPUT" | tail -1)" = "" ]; then
        LINE_COUNT=$((LINE_COUNT - 1))
    fi

    # Escribir resultado al archivo temporal
    echo "$LINE_COUNT" >> "$TEMP_DIR/results_tmp_$r"

    # Si supera 5500 operaciones, guardar el caso completo
    if [ "$LINE_COUNT" -gt 5500 ]; then
        local over_5500_file="$TEMP_DIR/over_5500_tmp_$r"
        {
            echo "┌─────────────────────────────────────────┐"
            echo "│             CASO CRÍTICO #$r"
            echo "└─────────────────────────────────────────┘"
            echo "OPERACIONES: $LINE_COUNT"
            echo "SECUENCIA: $NUMS"
            echo "COMANDO: ./push_swap $NUMS"
            echo ""
            echo "MOVIMIENTOS EJECUTADOS:"

            # Formatear los movimientos: 100 por línea
            local FORMATTED_MOVES=""
            local MOVE_COUNT=0
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
                        echo "$FORMATTED_MOVES"
                        FORMATTED_MOVES=""
                        MOVE_COUNT=0
                    fi
                fi
            done <<< "$PUSH_SWAP_OUTPUT"

            # Escribir los movimientos restantes si los hay
            if [ -n "$FORMATTED_MOVES" ]; then
                echo "$FORMATTED_MOVES"
            fi

            echo ""
            echo "═══════════════════════════════════════════════════════════"
            echo ""
        } > "$over_5500_file"

        # Actualizar contador de casos >5500
        echo "1" >> "$TEMP_DIR/count_5500_tmp_$r"
    fi

    # Guardar el caso y sus números en un archivo temporal
    echo "$LINE_COUNT:$NUMS" >> "$TEMP_DIR/results_cases_tmp_$r"

    # Marcar como completada (para la barra de progreso)
    touch "$TEMP_DIR/completed_$r"
}

# Iniciar ejecución
print_header "🚀 Iniciando ejecución de pruebas..."
echo ""

# Limpiar solo archivos temporales antiguos (que no sean el actual)
for old_temp in temp_*; do
    if [ -d "$old_temp" ] && [ "$old_temp" != "$TEMP_DIR" ]; then
        rm -rf "$old_temp" 2>/dev/null
    fi
done

# Tiempo de inicio
START_TIME=$(date +%s)

echo ""
print_info "Iniciando pruebas y monitoreando progreso..."
echo ""

# Contador de pruebas completadas
completadas=0
progress_shown=false

# Ejecutar pruebas en paralelo con monitoreo
for ((r=1; r<=repeticiones; r++)); do
    # Limitar el número de trabajos en paralelo
    while [ $(jobs -r | wc -l) -ge $MAX_JOBS ]; do
        # Mostrar progreso mientras esperamos
        completadas=$(ls "$TEMP_DIR"/completed_* 2>/dev/null | wc -l)
        tiempo_transcurrido=$(($(date +%s) - START_TIME))
        casos_5500=$(ls "$TEMP_DIR"/count_5500_tmp_* 2>/dev/null | wc -l)
        mostrar_progreso $completadas $repeticiones $tiempo_transcurrido $casos_5500
        sleep 0.2
    done

    # Ejecutar la prueba en segundo plano
    ejecutar_prueba $r $cantidad $min $max &

    # Pequeña pausa para evitar saturar el sistema
    if [ $((r % $MAX_JOBS)) -eq 0 ]; then
        sleep 0.1
    fi
done

# Monitoreo final hasta completar todas las pruebas
while [ $completadas -lt $repeticiones ]; do
    completadas=$(ls "$TEMP_DIR"/completed_* 2>/dev/null | wc -l)
    tiempo_transcurrido=$(($(date +%s) - START_TIME))
    casos_5500=$(ls "$TEMP_DIR"/count_5500_tmp_* 2>/dev/null | wc -l)

    mostrar_progreso $completadas $repeticiones $tiempo_transcurrido $casos_5500

    if [ $completadas -eq $repeticiones ]; then
        progress_shown=true
        break
    fi

    sleep 0.3
done

# Solo mostrar 100% si no se mostró antes
if [ "$progress_shown" = false ]; then
    tiempo_transcurrido=$(($(date +%s) - START_TIME))
    casos_5500=$(ls "$TEMP_DIR"/count_5500_tmp_* 2>/dev/null | wc -l)
    mostrar_progreso $repeticiones $repeticiones $tiempo_transcurrido $casos_5500
fi
echo ""

# Esperar a que terminen todos los trabajos
wait

END_TIME=$(date +%s)
TOTAL_TIME=$((END_TIME - START_TIME))

print_success "Todas las pruebas completadas en ${TOTAL_TIME}s"

# Consolidar archivos temporales
print_header "📊 Procesando resultados..."

cat "$TEMP_DIR"/results_tmp_* >> "$RESULTS_FILE" 2>/dev/null
cat "$TEMP_DIR"/over_5500_tmp_* >> "$OVER_5500_FILE" 2>/dev/null
cat "$TEMP_DIR"/results_cases_tmp_* > "$TEMP_DIR/results_cases_tmp" 2>/dev/null

# Calcular estadísticas detalladas
if [ -s "$RESULTS_FILE" ]; then
    SUM=0
    COUNT=0
    MAX_VAL=0
    MIN_VAL=999999
    OVER_5500=0
    declare -a DISTRIBUTION

    # Inicializar arrays de distribución
    for ((i=0; i<=10; i++)); do
        DISTRIBUTION[i]=0
    done

    while IFS= read -r line; do
        if [[ $line =~ ^[0-9]+$ ]]; then
            SUM=$((SUM + line))
            COUNT=$((COUNT + 1))

            if [ $line -gt $MAX_VAL ]; then
                MAX_VAL=$line
            fi
            if [ $line -lt $MIN_VAL ]; then
                MIN_VAL=$line
            fi
            if [ $line -gt 5500 ]; then
                OVER_5500=$((OVER_5500 + 1))
            fi

            # Distribución por rangos
            if [ $line -le 100 ]; then
                DISTRIBUTION[0]=$((DISTRIBUTION[0] + 1))
            elif [ $line -le 500 ]; then
                DISTRIBUTION[1]=$((DISTRIBUTION[1] + 1))
            elif [ $line -le 1000 ]; then
                DISTRIBUTION[2]=$((DISTRIBUTION[2] + 1))
            elif [ $line -le 2000 ]; then
                DISTRIBUTION[3]=$((DISTRIBUTION[3] + 1))
            elif [ $line -le 3000 ]; then
                DISTRIBUTION[4]=$((DISTRIBUTION[4] + 1))
            elif [ $line -le 4000 ]; then
                DISTRIBUTION[5]=$((DISTRIBUTION[5] + 1))
            elif [ $line -le 5000 ]; then
                DISTRIBUTION[6]=$((DISTRIBUTION[6] + 1))
            elif [ $line -le 5500 ]; then
                DISTRIBUTION[7]=$((DISTRIBUTION[7] + 1))
            elif [ $line -le 6000 ]; then
                DISTRIBUTION[8]=$((DISTRIBUTION[8] + 1))
            elif [ $line -le 7000 ]; then
                DISTRIBUTION[9]=$((DISTRIBUTION[9] + 1))
            else
                DISTRIBUTION[10]=$((DISTRIBUTION[10] + 1))
            fi
        fi
    done < <(tail -n +9 "$RESULTS_FILE")

    if [ $COUNT -gt 0 ]; then
        MEDIA=$(awk "BEGIN {printf \"%.2f\", $SUM/$COUNT}")

        # Calcular mediana
        sorted_values=($(tail -n +9 "$RESULTS_FILE" | grep -E '^[0-9]+$' | sort -n))
        if [ ${#sorted_values[@]} -gt 0 ]; then
            middle=$((${#sorted_values[@]} / 2))
            if [ $((${#sorted_values[@]} % 2)) -eq 0 ]; then
                MEDIANA=$(awk "BEGIN {printf \"%.1f\", (${sorted_values[$((middle-1))]} + ${sorted_values[$middle]}) / 2}")
            else
                MEDIANA=${sorted_values[$middle]}
            fi
        else
            MEDIANA="N/A"
        fi

        # Encontrar el caso con más movimientos
        MAX_MOV=0
        MAX_NUMS=""
        if [ -f "$TEMP_DIR/results_cases_tmp" ]; then
            while IFS=: read -r mov nums; do
                if [[ $mov =~ ^[0-9]+$ ]] && [ $mov -gt $MAX_MOV ]; then
                    MAX_MOV=$mov
                    MAX_NUMS=$nums
                fi
            done < "$TEMP_DIR/results_cases_tmp"

            if [ -n "$MAX_NUMS" ]; then
                echo "$MAX_NUMS" > "$MAX_CASE_FILE"
            fi
        fi

        # Preparar el resumen final con estadísticas detalladas
        SUMMARY="
═══════════════════════════════════════════════════════════
                        RESUMEN FINAL
═══════════════════════════════════════════════════════════
🎯 ESTADÍSTICAS BÁSICAS:
   Media de operaciones:           $MEDIA
   Mediana:                        $MEDIANA
   Valor mínimo:                   $MIN_VAL
   Valor máximo:                   $MAX_VAL
   Desviación del objetivo (5500): $((MAX_VAL - 5500))

📊 RENDIMIENTO:
   Casos totales ejecutados:       $COUNT
   Casos que superan 5500 ops:     $OVER_5500 ($(awk "BEGIN {printf \"%.1f\", $OVER_5500*100/$COUNT}")%)
   Casos dentro del objetivo:      $((COUNT - OVER_5500)) ($(awk "BEGIN {printf \"%.1f\", (($COUNT - $OVER_5500)*100/$COUNT)}")%)

⏱️  TIEMPO:
   Tiempo total de ejecución:      ${TOTAL_TIME}s ($(awk "BEGIN {printf \"%.1f\", $TOTAL_TIME/60}")m)
   Promedio por caso:              $(if [ $TOTAL_TIME -gt 0 ]; then awk "BEGIN {printf \"%.2f\", $TOTAL_TIME/$COUNT}"; else echo "0.00"; fi)s
   Throughput:                     $(if [ $TOTAL_TIME -gt 0 ]; then awk "BEGIN {printf \"%.1f\", $COUNT*60/$TOTAL_TIME}"; else echo "N/A"; fi) casos/min

📈 DISTRIBUCIÓN POR RANGOS:
   ≤ 100 operaciones:              ${DISTRIBUTION[0]} casos
   101-500 operaciones:            ${DISTRIBUTION[1]} casos
   501-1000 operaciones:           ${DISTRIBUTION[2]} casos
   1001-2000 operaciones:          ${DISTRIBUTION[3]} casos
   2001-3000 operaciones:          ${DISTRIBUTION[4]} casos
   3001-4000 operaciones:          ${DISTRIBUTION[5]} casos
   4001-5000 operaciones:          ${DISTRIBUTION[6]} casos
   5001-5500 operaciones:          ${DISTRIBUTION[7]} casos
   5501-6000 operaciones:          ${DISTRIBUTION[8]} casos
   6001-7000 operaciones:          ${DISTRIBUTION[9]} casos
   > 7000 operaciones:             ${DISTRIBUTION[10]} casos

═══════════════════════════════════════════════════════════
"

        # Escribir el resumen al principio del archivo
        {
            echo "$SUMMARY"
            echo ""
            echo "DATOS BRUTOS:"
            echo "─────────────"
        } > temp_results
        cat "$RESULTS_FILE" >> temp_results
        mv temp_results "$RESULTS_FILE"

        # Mostrar resumen en pantalla
        echo ""
        print_header "📈 RESUMEN DE RESULTADOS"
        echo -e "$SUMMARY"

        # Información adicional
        print_header "📁 Archivos generados:"
        print_success "Resultados principales: $RESULTS_FILE"
        print_success "Peor caso guardado en: $MAX_CASE_FILE"

        if [ $OVER_5500 -gt 0 ]; then
            print_warning "Casos problemáticos: $OVER_5500_FILE"
            print_info "Para revisar casos >5500: cat $OVER_5500_FILE"
        else
            print_success "¡Excelente! Ningún caso superó 5500 operaciones"
        fi

    else
        print_error "No se pudieron calcular estadísticas"
    fi
else
    print_error "No se encontraron resultados válidos"
fi

# Limpiar archivos temporales
rm -rf "$TEMP_DIR" 2>/dev/null

echo ""
print_header "🎉 Análisis completado exitosamente"
print_info "Directorio temporal $TEMP_DIR eliminado"
echo ""
