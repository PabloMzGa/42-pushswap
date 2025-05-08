/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:18:26 by pablo             #+#    #+#             */
/*   Updated: 2025/05/08 21:57:29 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void static	push_a(t_stack *stack_a, t_stack *stack_b)
{
	t_blist	*moving_node;

	moving_node = stack_b->top_element;
	stack_b->top_element = moving_node->next;
	if (stack_b->top_element)
		stack_b->top_element->previous = NULL;
	if (stack_a->size > 0 && stack_a->top_element)
	{
		moving_node->next = stack_a->top_element;
		stack_a->top_element->previous = moving_node;
	}
	else
	{
		moving_node->next = NULL;
		moving_node->previous = NULL;
	}
	stack_a->top_element = moving_node;
	stack_b->size--;
	stack_a->size++;
	write(1, "pa\n", 3);
}

void static	push_b(t_stack *stack_a, t_stack *stack_b)
{
	t_blist	*moving_node;

	moving_node = stack_a->top_element;
	stack_a->top_element = moving_node->next;
	if (stack_a->top_element)
		stack_a->top_element->previous = NULL;
	if (stack_b->size > 0 && stack_b->top_element)
	{
		moving_node->next = stack_b->top_element;
		stack_b->top_element->previous = moving_node;
	}
	else
	{
		moving_node->next = NULL;
		moving_node->previous = NULL;
	}
	stack_b->top_element = moving_node;
	stack_a->size--;
	stack_b->size++;
	write(1, "pb\n", 3);
}

void	push(t_stack *stack_a, t_stack *stack_b, char dir)
{
	if (dir == 'a')
	{
		if (stack_b->size == 0 || !stack_b->top_element)
			error(stack_a, stack_b);
		push_a(stack_a, stack_b);
	}
	else if (dir == 'b')
	{
		if (stack_a->size == 0 || !stack_a->top_element)
			error(stack_a, stack_b);
		push_b(stack_a, stack_b);
	}
	else
		error(stack_a, stack_b);
}
