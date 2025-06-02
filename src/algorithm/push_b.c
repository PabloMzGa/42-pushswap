/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 14:24:37 by pablo            ###   ########.fr       */
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

	i = 0;
	cost = calculate_cost(stack_a, stack_b, 1);
	while (stack_a->size > 0 && cost)
	{
		while (cost && (cost->src_stack_mov || cost->dst_stack_mov))
		{
			if (cost->src_stack_mov > 0 && cost->dst_stack_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->src_stack_mov < 0 && cost->dst_stack_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->src_stack_mov != 0)
				apply_a_rot(stack_a, cost, &cost->src_stack_mov);
			else if (cost->dst_stack_mov != 0)
				apply_b_rot(stack_b, cost, &cost->dst_stack_mov);
		}
		push(stack_a, stack_b, cost, 'b');
/* 		print_cost(cost, stack_a);
		print_stack(stack_a, 'a');
		print_stack(stack_b, 'b'); */
		free(cost);
/* 		if (stack_a->top_element->value == 0)
			ft_nothing((void *)&i); */
		cost = calculate_cost(stack_a, stack_b, 1);
		++i;
	}
}
