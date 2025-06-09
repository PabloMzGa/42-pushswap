/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:28:04 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 21:57:03 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Allocates and initializes an empty stack.
 *
 * This function creates a new stack structure by allocating memory for it.
 * The stack is initialized with no elements (top_element is set to NULL).
 *
 * @param id Character identifier for the stack ('A' or 'B').
 * @return A pointer to the newly created stack, or NULL if memory allocation
 * fails.
 */
static t_stack	*initialize_empty_stack(char id)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = NULL;
	stack->size = 0;
	stack->id = id;
	return (stack);
}

/**
 * @brief Initializes a stack with a single element at the top.
 *
 * This function allocates memory for a new stack and its top element.
 * The top element is initialized with the provided value. If any memory
 * allocation fails, the function ensures proper cleanup and returns NULL.
 *
 * @param top_value The value to initialize the top element of the stack with.
 * @param id Character identifier for the stack ('A' or 'B').
 *
 * @return A pointer to the newly created stack, or NULL if memory allocation
 * fails.
 */
static t_stack	*initialize_stack(int top_value, char id)
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
	stack->id = id;
	return (stack);
}

t_stack	*initialize_b_stack(t_stack *stack_a)
{
	t_stack	*stack_b;

	stack_b = initialize_empty_stack('B');
	if (!stack_b)
		return (NULL);
	push(stack_a, stack_b, NULL, 'b');
	push(stack_a, stack_b, NULL, 'b');
	return (stack_b);
}

t_stack	*populate_a_stack(int argc, char *argv[])
{
	int		value;
	int		i;
	t_stack	*stack_a;
	t_blist	*node;

	if (argc < 2)
		error(NULL, NULL, NULL);
	i = 0;
	value = is_arg_correct(argc, argv, i++, NULL);
	stack_a = initialize_stack(value, 'A');
	if (!stack_a)
		return (NULL);
	while (i < argc)
	{
		value = is_arg_correct(argc, argv, i++, stack_a);
		node = create_node(value);
		if (!node)
			error(stack_a, NULL, NULL);
		blstadd_back(&(stack_a->top_element), node);
	}
	stack_a->size = i;
	return (stack_a);
}
