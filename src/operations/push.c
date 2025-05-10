/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:18:26 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:44:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Moves the top element from stack_b to stack_a.
 *
 * This function performs the "push a" operation in the context of a stack-based
 * algorithm. It removes the top element from stack_b and places it on top of
 * stack_a. The sizes of both stacks are updated accordingly, and the operation
 * is logged by writing "pa\n" to the standard output.
 *
 * @param stack_a Pointer to the destination stack (stack_a).
 * @param stack_b Pointer to the source stack (stack_b).
 *
 * @note If stack_b is empty, this function may result in undefined behavior.
 * Ensure that stack_b has at least one element before calling this function.
 */
static void	push_a(t_stack *stack_a, t_stack *stack_b)
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

/**
 * @brief Moves the top element from stack_a to stack_b.
 *
 * This function performs the "push b" operation in the context of a stack-based
 * algorithm. It removes the top element from stack_a and places it on top of
 * stack_b. The sizes of both stacks are updated accordingly, and the operation
 * is logged by writing "pb\n" to the standard output.
 *
 * @param stack_a Pointer to the destination stack (stack_a).
 * @param stack_b Pointer to the source stack (stack_b).
 *
 * @note If stack_a is empty, this function may result in undefined behavior.
 * Ensure that stack_b has at least one element before calling this function.
 */
static void	push_b(t_stack *stack_a, t_stack *stack_b)
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

/**
 * @brief Pushes the top element from one stack to another based on the
 *        direction.
 *
 * This function transfers the top element from one stack to another.
 * The direction of the push is determined by the `dir` parameter:
 *
 * - 'a': Pushes the top element from stack_b to stack_a.
 *
 * - 'b': Pushes the top element from stack_a to stack_b.
 *
 * If the source stack is empty or its top element is NULL, the function calls
 * the `error` function to handle the error.
 *
 * @param stack_a Pointer to the first stack (stack_a).
 * @param stack_b Pointer to the second stack (stack_b).
 * @param dir A character indicating the direction of the push ('a' or 'b').
 *
 * @note If an invalid direction is provided, the function calls the `error`
 *       function.
 */
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
