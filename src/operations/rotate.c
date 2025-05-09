/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:09:51 by pablo             #+#    #+#             */
/*   Updated: 2025/05/09 12:48:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Rotates a stack by moving the top element to the bottom.
 *
 * This function takes the top element of the stack, removes it from the top,
 * and appends it to the bottom of the stack. It also sets the second element as
 * the top element, effectively rotating the stack
 * upwards by one position. I
 *
 * @param stack A pointer to the stack to be rotated. The stack must be
 *              properly initialized and contain at least one element.
 */
static void	reverse_rotate_stack(t_stack *stack)
{
	t_blist	*top_node;

	top_node = stack->top_element;
	stack->top_element = top_node->next;
	stack->top_element->previous = NULL;
	top_node->next = NULL;
	top_node->previous = NULL;
	blstadd_back(&(stack->top_element), top_node);
}

void	rotate(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a && !stack_b)
	{
		if (!stack_a->top_element || stack_a->size <= 1)
			error(stack_a, stack_b);
		reverse_rotate_stack(stack_a);
		write(1, "ra\n", 3);
	}
	else if (!stack_a && stack_b)
	{
		if (!stack_b->top_element || stack_b->size <= 1)
			error(stack_a, stack_b);
		reverse_rotate_stack(stack_b);
		write(1, "rb\n", 3);
	}
	else if (stack_a && stack_b)
	{
		if (!stack_a->top_element || !stack_b->top_element || stack_b->size <= 1
			|| stack_a->size <= 1)
			error(stack_a, stack_b);
		reverse_rotate_stack(stack_a);
		reverse_rotate_stack(stack_b);
		write(1, "rr\n", 3);
	}
}
