/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:51 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:24:27 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Reverses the order of elements in a stack by moving the last element
 *        to the top of the stack.
 *
 * This function modifies the given stack by taking the last node (element)
 * and placing it at the top of the stack. It adjusts the pointers of the
 * doubly linked list to maintain the stack structure.
 *
 * @param stack A pointer to the stack to be modified. The stack is represented
 *              as a structure containing a pointer to the top element.
 */
static void	reverse_rotate_stack(t_stack *stack)
{
	t_blist	*last_node;

	last_node = get_last_node(stack->top_element);
	last_node->previous->next = NULL;
	stack->top_element->previous = last_node;
	last_node->previous = NULL;
	last_node->next = stack->top_element;
	stack->top_element = last_node;
}

void	reverse_rotate(t_stack *stack_a, t_stack *stack_b, t_cost *cost)
{
	if (stack_a && !stack_b)
	{
		if (!stack_a->top_element || stack_a->size <= 1)
			error(stack_a, stack_b, cost);
		reverse_rotate_stack(stack_a);
		write(1, "rra\n", 4);
	}
	else if (!stack_a && stack_b)
	{
		if (!stack_b->top_element || stack_b->size <= 1)
			error(stack_a, stack_b, cost);
		reverse_rotate_stack(stack_b);
		write(1, "rrb\n", 4);
	}
	else if (stack_a && stack_b)
	{
		if (!stack_a->top_element || !stack_b->top_element || stack_b->size <= 1
			|| stack_a->size <= 1)
			error(stack_a, stack_b, cost);
		reverse_rotate_stack(stack_a);
		reverse_rotate_stack(stack_b);
		write(1, "rrr\n", 4);
	}
}
