/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 18:46:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_a->size > 0)
	{
		//print_stack(stack_a, 'a');
		//print_stack(stack_b, 'b');
		/*
		if (stack_a->top_element->value == 1 && stack_b->top_element->value == 14)
			printf("a"); */
		cost = calculate_cost(stack_a, stack_b);
		//print_cost(cost, stack_a);
		while (cost->stack_a_mov || cost->stack_b_mov)
		{
			if (cost->stack_a_mov > 0 && cost->stack_b_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->stack_a_mov < 0 && cost->stack_b_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->stack_a_mov != 0)
				apply_a_rot(stack_a, &cost->stack_a_mov);
			else if (cost->stack_b_mov != 0)
				apply_b_rot(stack_b, &cost->stack_b_mov);
 			//print_stack(stack_a, 'a');
			//print_stack(stack_b, 'b');
		}
		push(stack_a, stack_b, 'b');
		free(cost);
	}
}
