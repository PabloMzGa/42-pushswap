#!/bin/bash

# Script para testear diferentes valores de SWAP_THRESHOLD
# Genera casos de prueba y encuentra el valor óptimo

# Configuración
NUM_CASES=100
TEST_SIZE=500
RESULTS_DIR="threshold_results"

# Rangos de valores a testear
THRESHOLD_VALUES=(0 )

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Script de Optimización SWAP_THRESHOLD ===${NC}"

# Crear directorio de resultados si no existe
mkdir -p "$RESULTS_DIR"

# Función para verificar si existen casos de prueba
check_existing_test_cases() {
    local cases_found=0

    # Verificar si existe el directorio y los archivos de casos
    if [ -d "$RESULTS_DIR" ]; then
        for i in $(seq 1 $NUM_CASES); do
            if [ -f "$RESULTS_DIR/case_$i.txt" ]; then
                cases_found=$((cases_found + 1))
            fi
        done
    fi

    echo $cases_found
}

# Función para mostrar información de casos existentes
show_existing_cases_info() {
    local existing_cases=$(check_existing_test_cases)

    if [ $existing_cases -gt 0 ]; then
        echo -e "${GREEN}Se encontraron $existing_cases casos de prueba existentes en $RESULTS_DIR/${NC}"

        # Mostrar información adicional si existe
        if [ -f "$RESULTS_DIR/test_cases.txt" ]; then
            local file_size=$(du -h "$RESULTS_DIR/test_cases.txt" 2>/dev/null | cut -f1)
            echo -e "${YELLOW}Archivo principal: test_cases.txt ($file_size)${NC}"
        fi

        # Mostrar algunos archivos de ejemplo
        echo -e "${YELLOW}Archivos encontrados:${NC}"
        ls -la "$RESULTS_DIR"/case_*.txt 2>/dev/null | head -5
        if [ $existing_cases -gt 5 ]; then
            echo "... y $((existing_cases - 5)) más"
        fi
    else
        echo -e "${YELLOW}No se encontraron casos de prueba existentes${NC}"
    fi
}

# Función para preguntar al usuario qué hacer con los casos de prueba
ask_about_test_cases() {
    local existing_cases=$(check_existing_test_cases)

    if [ $existing_cases -gt 0 ]; then
        echo ""
        show_existing_cases_info
        echo ""
        echo -e "${BLUE}¿Qué deseas hacer con los casos de prueba?${NC}"
        echo "1) Usar los casos existentes ($existing_cases casos)"
        echo "2) Generar nuevos casos ($NUM_CASES casos de $TEST_SIZE elementos)"
        echo "3) Salir"
        echo ""

        while true; do
            read -p "Selecciona una opción (1-3): " choice
            case $choice in
                1)
                    echo -e "${GREEN}Usando casos de prueba existentes...${NC}"
                    return 0
                    ;;
                2)
                    echo -e "${YELLOW}Se generarán nuevos casos de prueba...${NC}"
                    return 1
                    ;;
                3)
                    echo -e "${BLUE}Saliendo...${NC}"
                    exit 0
                    ;;
                *)
                    echo -e "${RED}Opción inválida. Por favor selecciona 1, 2 o 3.${NC}"
                    ;;
            esac
        done
    else
        echo -e "${YELLOW}No se encontraron casos existentes. Generando $NUM_CASES casos de prueba con $TEST_SIZE elementos cada uno...${NC}"
        return 1
    fi
}

# Función para validar que los casos existentes están completos
validate_existing_cases() {
    local missing_cases=0
    local invalid_cases=0

    echo -e "${YELLOW}Validando casos de prueba existentes...${NC}"

    for i in $(seq 1 $NUM_CASES); do
        case_file="$RESULTS_DIR/case_$i.txt"

        if [ ! -f "$case_file" ]; then
            missing_cases=$((missing_cases + 1))
        else
            # Verificar que el archivo no esté vacío y tenga el formato correcto
            word_count=$(wc -w < "$case_file" 2>/dev/null)
            if [ "$word_count" -ne $TEST_SIZE ]; then
                invalid_cases=$((invalid_cases + 1))
            fi
        fi
    done

    if [ $missing_cases -gt 0 ] || [ $invalid_cases -gt 0 ]; then
        echo -e "${RED}Problemas encontrados en los casos existentes:${NC}"
        [ $missing_cases -gt 0 ] && echo -e "${RED}  - $missing_cases casos faltantes${NC}"
        [ $invalid_cases -gt 0 ] && echo -e "${RED}  - $invalid_cases casos con formato incorrecto${NC}"

        echo -e "${YELLOW}Se recomienda generar nuevos casos de prueba.${NC}"
        echo -e "${BLUE}¿Deseas continuar con los casos existentes válidos o generar nuevos?${NC}"
        echo "1) Continuar con casos válidos"
        echo "2) Generar nuevos casos"

        while true; do
            read -p "Selecciona una opción (1-2): " choice
            case $choice in
                1)
                    echo -e "${YELLOW}Continuando con casos válidos...${NC}"
                    return 0
                    ;;
                2)
                    return 1
                    ;;
                *)
                    echo -e "${RED}Opción inválida. Por favor selecciona 1 o 2.${NC}"
                    ;;
            esac
        done
    else
        echo -e "${GREEN}Todos los casos existentes son válidos${NC}"
        return 0
    fi
}

# Función para generar casos de prueba
generate_test_cases() {
    echo -e "${YELLOW}Generando casos de prueba...${NC}"

    # Limpiar casos anteriores si existen
    rm -f "$RESULTS_DIR"/case_*.txt
    rm -f "$RESULTS_DIR/test_cases.txt"

    # Archivo con todos los casos
    echo "" > "$RESULTS_DIR/test_cases.txt"

    for i in $(seq 1 $NUM_CASES); do
        # Generar números aleatorios únicos
        case_file="$RESULTS_DIR/case_$i.txt"
        python3 -c "
import random
numbers = random.sample(range(1, 1000), $TEST_SIZE)
print(' '.join(map(str, numbers)))
" > "$case_file"

        # Añadir al archivo principal
        cat "$case_file" >> "$RESULTS_DIR/test_cases.txt"
        echo "" >> "$RESULTS_DIR/test_cases.txt"

        if [ $((i % 20)) -eq 0 ]; then
            echo -e "${BLUE}Generados $i/$NUM_CASES casos...${NC}"
        fi
    done

    echo -e "${GREEN}Casos de prueba generados exitosamente${NC}"
}

# Función para compilar el proyecto con un threshold específico
compile_project_with_threshold() {
    local threshold=$1

    echo -e "${YELLOW}Compilando proyecto con SWAP_THRESHOLD = $threshold...${NC}"

    # Limpiar compilación anterior
    make fclean > /dev/null 2>&1

    # Compilar con la macro definida usando CFLAGS
    make CFLAGS="-Wall -Wextra -Werror -g -DSWAP_THRESHOLD=$threshold" > /dev/null 2>&1

    if [ $? -eq 0 ] && [ -f "build/push_swap" ]; then
        echo -e "${GREEN}Compilación exitosa con SWAP_THRESHOLD = $threshold${NC}"
        return 0
    else
        echo -e "${RED}Error en la compilación con SWAP_THRESHOLD = $threshold${NC}"
        return 1
    fi
}

# Función para testear un threshold específico
test_threshold() {
    local threshold=$1
    local result_file="$RESULTS_DIR/results_$threshold.txt"
    local total_operations=0
    local successful_cases=0
    local cases_over_5500=0

    echo -e "${BLUE}Testeando SWAP_THRESHOLD = $threshold${NC}"

    # Compilar con el threshold específico
    compile_project_with_threshold "$threshold"
    if [ $? -ne 0 ]; then
        return 1
    fi

    # Crear archivo de resultados
    echo "SWAP_THRESHOLD: $threshold" > "$result_file"
    echo "================================" >> "$result_file"
    echo "" >> "$result_file"

    # Testear cada caso
    for i in $(seq 1 $NUM_CASES); do
        case_file="$RESULTS_DIR/case_$i.txt"

        if [ -f "$case_file" ]; then
            # Ejecutar push_swap y contar operaciones
            case_input=$(cat "$case_file")
            operations=$(timeout 10s ./build/push_swap $case_input 2>/dev/null | wc -l)

            if [ $? -eq 0 ] && [ "$operations" -gt 0 ]; then
                echo "Caso $i: $operations operaciones" >> "$result_file"
                total_operations=$((total_operations + operations))
                successful_cases=$((successful_cases + 1))

                # Contar casos que superan 5500 movimientos
                if [ "$operations" -gt 5500 ]; then
                    cases_over_5500=$((cases_over_5500 + 1))
                    echo "Caso $i: $operations operaciones (>5500)" >> "$result_file"
                    # También guardar en archivo especial para casos problemáticos
                    echo "Threshold $threshold - Caso $i: $operations operaciones" >> "$RESULTS_DIR/cases_over_5500.txt"
                fi
            else
                echo "Caso $i: ERROR o TIMEOUT" >> "$result_file"
            fi
        fi

        # Mostrar progreso cada 25 casos
        if [ $((i % 25)) -eq 0 ]; then
            echo -e "${YELLOW}  Procesados $i/$NUM_CASES casos para threshold $threshold${NC}"
        fi
    done

    # Calcular promedio
    if [ $successful_cases -gt 0 ]; then
        avg_operations=$((total_operations / successful_cases))
        echo "" >> "$result_file"
        echo "================================" >> "$result_file"
        echo "RESUMEN:" >> "$result_file"
        echo "Casos exitosos: $successful_cases/$NUM_CASES" >> "$result_file"
        echo "Total operaciones: $total_operations" >> "$result_file"
        echo "Promedio operaciones: $avg_operations" >> "$result_file"
        echo "Casos > 5500 movimientos: $cases_over_5500/$successful_cases" >> "$result_file"

        echo -e "${GREEN}Threshold $threshold: $avg_operations operaciones promedio ($successful_cases casos exitosos, $cases_over_5500 casos >5500)${NC}"

        # Guardar resultado en archivo de resumen
        echo "$threshold,$avg_operations,$successful_cases,$cases_over_5500" >> "$RESULTS_DIR/summary.csv"
    else
        echo -e "${RED}Threshold $threshold: Ningún caso exitoso${NC}"
        echo "$threshold,ERROR,0,0" >> "$RESULTS_DIR/summary.csv"
    fi
}

# Función para analizar resultados
analyze_results() {
    echo -e "${BLUE}=== ANÁLISIS DE RESULTADOS ===${NC}"

    if [ ! -f "$RESULTS_DIR/summary.csv" ]; then
        echo -e "${RED}No se encontraron resultados para analizar${NC}"
        return 1
    fi

    echo -e "${YELLOW}Resumen por threshold:${NC}"
    echo "Threshold | Promedio Ops | Casos Exitosos | Casos >5500"
    echo "----------|--------------|----------------|------------"

    while IFS=',' read -r threshold avg_ops successful_cases cases_over_5500; do
        if [ "$avg_ops" != "ERROR" ]; then
            printf "%-9s | %-12s | %-14s | %s\n" "$threshold" "$avg_ops" "$successful_cases" "$cases_over_5500"
        else
            printf "%-9s | %-12s | %-14s | %s\n" "$threshold" "ERROR" "$successful_cases" "$cases_over_5500"
        fi
    done < "$RESULTS_DIR/summary.csv"

    echo ""

    # Encontrar el mejor threshold
    best_threshold=$(awk -F',' '$2 != "ERROR" {print $2 "," $1}' "$RESULTS_DIR/summary.csv" | sort -n | head -1 | cut -d',' -f2)
    best_avg=$(awk -F',' '$2 != "ERROR" {print $2 "," $1}' "$RESULTS_DIR/summary.csv" | sort -n | head -1 | cut -d',' -f1)

    if [ -n "$best_threshold" ]; then
        echo -e "${GREEN}🏆 MEJOR THRESHOLD: $best_threshold (promedio: $best_avg operaciones)${NC}"

        # Generar recomendación
        echo ""
        echo -e "${BLUE}Recomendación:${NC}"
        echo "Cambiar el valor en src/algorithm/push_b.c:"
        echo "# define SWAP_THRESHOLD $best_threshold"
    else
        echo -e "${RED}No se pudo determinar el mejor threshold${NC}"
    fi
}

# Función principal
main() {
    echo -e "${BLUE}Iniciando proceso de optimización...${NC}"

    # Verificar que existe el ejecutable Python
    if ! command -v python3 &> /dev/null; then
        echo -e "${RED}Error: Python3 no está instalado${NC}"
        exit 1
    fi

    # Preguntar sobre los casos de prueba
    ask_about_test_cases
    use_existing=$?

    # Si se decide usar casos existentes, validarlos
    if [ $use_existing -eq 0 ]; then
        validate_existing_cases
        if [ $? -ne 0 ]; then
            generate_test_cases
        fi
    else
        # Generar nuevos casos
        generate_test_cases
    fi

    # Crear archivo de resumen CSV
    echo "threshold,avg_operations,successful_cases,cases_over_5500" > "$RESULTS_DIR/summary.csv"

    # Crear archivo para casos problemáticos
    echo "Casos que superan 5500 movimientos:" > "$RESULTS_DIR/cases_over_5500.txt"
    echo "===================================" >> "$RESULTS_DIR/cases_over_5500.txt"
    echo "" >> "$RESULTS_DIR/cases_over_5500.txt"

    # Testear cada threshold
    for threshold in "${THRESHOLD_VALUES[@]}"; do
        test_threshold "$threshold"
        echo ""
    done

    # Compilación final con valores por defecto
    echo -e "${YELLOW}Restaurando compilación con valores por defecto...${NC}"
    make fclean > /dev/null 2>&1
    make > /dev/null 2>&1

    # Analizar resultados
    analyze_results

    echo ""
    echo -e "${GREEN}Proceso completado. Resultados guardados en: $RESULTS_DIR/${NC}"
    echo -e "${YELLOW}Archivos generados:${NC}"
    echo "  - $RESULTS_DIR/summary.csv (resumen con casos >5500)"
    echo "  - $RESULTS_DIR/results_*.txt (resultados detallados)"
    echo "  - $RESULTS_DIR/cases_over_5500.txt (casos problemáticos)"
    echo "  - $RESULTS_DIR/test_cases.txt (casos de prueba)"
}

# Ejecutar función principal
main "$@"
