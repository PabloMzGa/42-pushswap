/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 14:31:03 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/* void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	int	index;
	int	movements;
	int	min_value;
	int	min_index;
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

static void	correct_a_rot(t_stack *stack_a)
{

	int min_index;
	int movements;

	min_index = get_lowest_node(stack_a->top_element);
	movements = get_top_distance(min_index, stack_a);
	while (movements != 0)
	{
		if (movements > 0)
			rotate(stack_a, NULL, NULL);
		else
			reverse_rotate(stack_a, NULL, NULL);
		if (movements > 0)
			movements--;
		else
			movements++;
	}
}

void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;
	int		i;

	i = 0;
/* 	print_stack(stack_a, 'a');
	print_stack(stack_b, 'b'); */
	cost = calculate_cost(stack_b, stack_a, 0);
/* 	print_cost(cost, stack_b); */
	while (stack_b->size > 0 && cost)
	{
		/* 		if (!cost)
					error(stack_a, stack_b, NULL); */
		while (cost && (cost->src_stack_mov || cost->dst_stack_mov))
		{
			if (cost->src_stack_mov > 0 && cost->dst_stack_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->src_stack_mov < 0 && cost->dst_stack_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->dst_stack_mov != 0)
				apply_a_rot(stack_a, cost, &cost->dst_stack_mov);
			else if (cost->src_stack_mov != 0)
				apply_b_rot(stack_b, cost, &cost->src_stack_mov);
		}
		push(stack_a, stack_b, cost, 'a');
		free(cost);
		cost = calculate_cost(stack_b, stack_a, 0);
/* 		print_stack(stack_a, 'a');
		print_stack(stack_b, 'b');
		print_cost(cost, stack_b); */
		++i;
	}
	correct_a_rot(stack_a);
}
