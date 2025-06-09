/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 21:59:52 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Rotates stack_a so that the highest value node is positioned at the
 *        bottom.
 *
 * This function locates the node with the highest value in stack_a and performs
 * either rotations or reverse-rotations to move it to the bottom of the stack,
 * choosing the shortest path. After execution, the lowest value will be at the
 * top of the stack.
 *
 * @param stack_a Pointer to the stack to be rotated.
 */
static void	final_sort_stack_a(t_stack *stack_a)
{
	int	max_position;

	max_position = get_highest_node(stack_a->top_element);
	if (max_position == -1)
		return ;
	if (max_position == stack_a->size - 1)
		return ;
	if (max_position < stack_a->size / 2)
	{
		while (max_position > -1)
		{
			rotate(stack_a, NULL, NULL);
			max_position--;
		}
	}
	else
	{
		while (max_position < stack_a->size - 1)
		{
			reverse_rotate(stack_a, NULL, NULL);
			max_position++;
		}
	}
}

void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	cost = NULL;
	while (stack_b->size > 0)
	{
		cost = calculate_cost(stack_b, stack_a);
		if (!cost)
			break ;
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
		}
		push(stack_a, stack_b, cost, 'a');
		ft_free((void **)&cost);
	}
	final_sort_stack_a(stack_a);
}
