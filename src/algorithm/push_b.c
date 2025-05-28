/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/05/28 17:54:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	is_inside_range(t_stack *stack, int min, int max)
{
	t_blist	*node;

	node = stack->top_element;
	while (node)
	{
		if (node->value >= min && node->value < max)
			return (1);
		node = node->next;
	}
	return (0);
}

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;
	int		i;
	int		current_chunk;

	i = 0;
	current_chunk = 0;
	while (stack_a->size > 0)
	{
/* 		if (current_chunk == 0 && !is_inside_range(stack_a, 0, 100))
			++current_chunk;
		else if (current_chunk == 1 && !is_inside_range(stack_a, 100, 200))
			++current_chunk;
		else if (current_chunk == 2 && !is_inside_range(stack_a, 200, 300))
			++current_chunk;
		else if (current_chunk == 3 && !is_inside_range(stack_a, 300, 400))
			++current_chunk;
		else if (current_chunk == 4 && !is_inside_range(stack_a, 400, 501))
			++current_chunk; */
		// print_stack(stack_a, 'a');
		// print_stack(stack_b, 'b');
		cost = calculate_cost(stack_a, stack_b, current_chunk);
		// print_cost(cost, stack_a);
		if (!cost)
			error(stack_a, stack_b, NULL);
		while (cost->stack_a_mov || cost->stack_b_mov)
		{
			if (cost->stack_a_mov > 0 && cost->stack_b_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->stack_a_mov < 0 && cost->stack_b_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->stack_a_mov != 0)
				apply_a_rot(stack_a, cost, &cost->stack_a_mov);
			else if (cost->stack_b_mov != 0)
				apply_b_rot(stack_b, cost, &cost->stack_b_mov);
		}
		push(stack_a, stack_b, cost, 'b');
		free(cost);
		++i;
	}
}
