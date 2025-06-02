/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 20:57:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/* void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	int	index;
	int	movements;

	while (stack_b->size > 1)
	{
		index = get_highest_node(stack_b->top_element);
		movements = get_top_distance(index, stack_b);
		while (movements != 0)
			apply_b_rot(stack_b, NULL, &movements);
		push(stack_a, stack_b, NULL, 'a');
	}
	push(stack_a, stack_b, NULL, 'a');
} */

void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_b->size > 0)
	{
		cost = calculate_cost(stack_b, stack_a, 0);
		if (!cost)
			break;
		while (cost->stack_a_mov || cost->stack_b_mov)
		{
			if (cost->stack_a_mov > 0 && cost->stack_b_mov > 0)
				apply_double_rot(stack_b, stack_a, cost);
			else if (cost->stack_a_mov < 0 && cost->stack_b_mov < 0)
				apply_double_rot(stack_b, stack_a, cost);
			else if (cost->stack_a_mov != 0)
				apply_a_rot(stack_b, cost, &cost->stack_a_mov);
			else if (cost->stack_b_mov != 0)
				apply_b_rot(stack_a, cost, &cost->stack_b_mov);
		}
		push(stack_b, stack_a, cost, 'a');
		free(cost);
	}
}
