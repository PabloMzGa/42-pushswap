/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/06/04 21:22:13 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Checks if a stack is sorted in ascending order (from top to bottom)
 *
 * This function traverses a stack from top to bottom and verifies that each
 * element is less than the next element, ensuring the stack is
 * sorted in ascending order.
 *
 * @param stack Pointer to the stack structure to check
 * @return 1 if the stack is sorted in ascending order, 0 otherwise
 */
static int	is_stack_sorted(t_stack *stack)
{
	t_blist	*current;

	if (!stack || !stack->top_element)
		return (1);
	if (stack->size < 1)
		return (1);
	current = stack->top_element;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

/**
 * TODO: Parece que en la mayoría de casos, no merce la pena hacer este swap.
 * Diría que los casos en los que se son los que hay una diferencia muy bestia
 * entre parejas. Quizás habría que hacer un "scooping" primero
 * para poder tomar la decisión de activarlo o no
 */
/**
 * @brief Checks if swapping would improve distribution balance
 *
 * This function evaluates whether swapping the top two elements would help
 * avoid extreme distributions by keeping larger values lower in the stack.
 * Simple logic: if the first element is significantly larger than the second,
 * swap to push the larger value down.
 *
 * @param stack_a Pointer to stack A
 * @param stack_b Pointer to stack B (unused but kept for compatibility)
 * @return 1 if swap would be beneficial, 0 otherwise
 */
int	should_swap_during_algorithm(t_stack *stack_a, t_stack *stack_b)
{
	int	top_value;
	int	second_value;
	int	difference;

	(void)stack_b;  // Parámetro mantenido por compatibilidad

	if (stack_a->size < 2)
		return (0);

	top_value = stack_a->top_element->value;
	second_value = stack_a->top_element->next->value;

	// Si el primer elemento es significativamente mayor que el segundo,
	// hacer swap para empujar el mayor hacia abajo
	difference = top_value - second_value;

	// Swap si la diferencia es significativa (más del 20% del valor menor)
	// Esto evita distribuciones extremas como (400, 14, 350, 70)
	#ifndef SWAP_THRESHOLD
	# define SWAP_THRESHOLD 0
	#endif
	if(SWAP_THRESHOLD == 0)
		return (0);
	if (difference > 0 && difference > (second_value / SWAP_THRESHOLD))
		return (1);

	return (0);
}

/**
 * 1, 2, 3 - Ya ordenado				OK
 * 1, 3, 2 - Intercambiar 2 y 3			OK
 * 2, 1, 3 - Intercambiar 1 y 2			OK
 * 2, 3, 1 - Rotar hacia la izquierda	OK
 * 3, 1, 2 - Rotar hacia la derecha
 * 3, 2, 1 - Orden inverso				OK
 */

static void sort_3(t_stack *stack)
{
	int n1;
	int n2;
	int n3;

	n1 = stack->top_element->value;
	n2 = stack->top_element->next->value;
	n3 = stack->top_element->next->next->value;
	if (n1 < n2 && n2 < n3)
		return;
	else if (n1 < n2 && n1 < n3 && n2 > n3)
	{
		reverse_rotate(stack, NULL, NULL);
		swap(stack, NULL);
	}
	else if (n1 > n2 && n1 < n3 && n2 < n3)
		swap(stack, NULL);
	else if (n1 < n2 && n1 > n3 && n2 > n3)
		reverse_rotate(stack, NULL, NULL);
	else if (n1 > n2 && n1 > n3 && n2 < n3)
		rotate(stack, NULL, NULL);
	else if(n1 > n2 && n1 > n3 && n2 > n3)
	{
		rotate(stack, NULL, NULL);
		swap(stack, NULL);
	}
}

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;
	int		i;

	i = 0;
	while (stack_a->size > 3 && !is_stack_sorted(stack_a))
	{
		// Verificar si vale la pena hacer swap antes de calcular costos
		if (should_swap_during_algorithm(stack_a, stack_b))
			swap(stack_a, NULL);
/* 		 print_stack(stack_a, 'a');
		 print_stack(stack_b, 'b'); */
		cost = calculate_cost(stack_a, stack_b);
/* 		 print_cost(cost, stack_a); */
		if (!cost)
			break;
		while (cost->source_mov || cost->dest_mov)
		{
			if (cost->source_mov > 0 && cost->dest_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov < 0 && cost->dest_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov != 0)
				apply_a_rot(stack_a, cost, &cost->source_mov);
			else if (cost->dest_mov != 0)
				apply_b_rot(stack_b, cost, &cost->dest_mov);
		}
		push(stack_a, stack_b, cost, 'b');
		free(cost);
		++i;
	}
	if (stack_a->size == 3)
		sort_3(stack_a);
}
