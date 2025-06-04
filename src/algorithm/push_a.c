/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/04 11:15:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


/**
 * @brief Encuentra la posición del elemento más pequeño en el stack
 *
 * @param stack Puntero al stack donde buscar
 * @return Índice del elemento más pequeño (0 = top)
 */
static int	find_min_position(t_stack *stack)
{
	t_blist	*current;
	int		min_value;
	int		min_position;
	int		current_position;

	if (!stack || !stack->top_element)
		return (-1);
	current = stack->top_element;
	min_value = current->value;
	min_position = 0;
	current_position = 0;
	while (current)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_position = current_position;
		}
		current = current->next;
		current_position++;
	}
	return (min_position);
}

/**
 * @brief Rota el stack A hasta que el elemento más pequeño esté en el top
 *
 * @param stack_a Puntero al stack A
 */
static void	final_sort_stack_a(t_stack *stack_a)
{
	int		min_position;
	int		stack_size;
	int		moves_needed;

	min_position = find_min_position(stack_a);
	if (min_position == -1 || min_position == 0)
		return;
	stack_size = stack_a->size;
	moves_needed = min_position;

	// Decidir si rotar hacia arriba o hacia abajo
	if (moves_needed <= stack_size / 2)
	{
		// Rotar hacia arriba (ra)
		while (moves_needed > 0)
		{
			rotate(stack_a, NULL, NULL);
			moves_needed--;
		}
	}
	else
	{
		// Rotar hacia abajo (rra)
		moves_needed = stack_size - moves_needed;
		while (moves_needed > 0)
		{
			reverse_rotate(stack_a, NULL, NULL);
			moves_needed--;
		}
	}
}


void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	cost = NULL;
	while (stack_b->size > 0)
	{
/* 		ft_printf("STACKS ANTES DE MOVERSE\n");
		print_stack(stack_a, 'A');
		print_stack(stack_b, 'B');
		ft_printf("\n ======================= \n"); */
		cost = calculate_cost(stack_b, stack_a, 0);
/* 		print_cost(cost, stack_b); */
		if (!cost)
		break;
		while (cost->source_mov || cost->dest_mov)
		{
			if (cost->source_mov > 0 && cost->dest_mov > 0)
			apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov < 0 && cost->dest_mov < 0)
			apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov != 0)
			apply_b_rot(stack_b, cost, &cost->source_mov);
			else if (cost->dest_mov != 0)
			apply_a_rot(stack_a, cost, &cost->dest_mov);
/* 			print_stack(stack_a, 'A');
			print_stack(stack_b, 'B'); */
		}
		push(stack_a, stack_b, cost, 'a');
/* 		ft_printf("STACKS DESPUÉS DE MOVERSE\n");
		print_stack(stack_a, 'A');
		print_stack(stack_b, 'B');
		ft_printf("\n ======================= \n"); */
		free(cost);
	}

	// Rotación final para asegurar que el elemento más pequeño esté en el top
/* 	ft_printf("ROTACIÓN FINAL PARA ORDENAR STACK A\n"); */
	final_sort_stack_a(stack_a);
/* 	ft_printf("STACK A FINAL ORDENADO:\n");
	print_stack(stack_a, 'A'); */
}
