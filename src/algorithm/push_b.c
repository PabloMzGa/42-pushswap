/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:25:31 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_a->size > 0)
	{
		cost = calculate_cost(stack_a, stack_b);
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
	}
}
