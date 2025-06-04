/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/06/04 12:31:45 by pablo            ###   ########.fr       */
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

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;
	int		i;

	i = 0;
	while (stack_a->size > 1 && !is_stack_sorted(stack_a))
	{

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
}
