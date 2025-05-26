/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:28:04 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:17:42 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_stack	*initialize_empty_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = NULL;
	stack->size = 0;
	return (stack);
}

t_stack	*initialize_stack(int top_value)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = malloc(sizeof(t_blist));
	if (!stack->top_element)
		return (free(stack), NULL);
	stack->top_element->value = top_value;
	stack->top_element->next = NULL;
	stack->top_element->previous = NULL;
	stack->size = 1;
	return (stack);
}

t_stack	*initialize_b_stack(t_stack *stack_a)
{
	t_stack	*stack_b;

	stack_b = initialize_empty_stack();
	push(stack_a, stack_b, NULL, 'b');
	push(stack_a, stack_b, NULL, 'b');
	return (stack_b);
}
