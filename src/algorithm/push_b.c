/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/06/12 21:44:00 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_a->size > 3 && !is_stack_sorted(stack_a))
	{
		cost = calculate_cost(stack_a, stack_b);
		if (!cost)
			break ;
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
		ft_free((void **)&cost);
	}
	if (stack_a->size == 3)
		sort_3(stack_a);
}
