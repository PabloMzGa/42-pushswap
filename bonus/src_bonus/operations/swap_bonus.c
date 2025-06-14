/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:56:44 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 18:47:28 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/**
 * @brief Swaps the first two elements of a stack.
 *
 * This function modifies the given stack by swapping the positions of the
 * first two elements (top two elements). If the stack is empty or contains
 * only one element, the function does nothing.
 *
 * @param stack A pointer to the stack to be modified. The stack must be
 *              properly initialized and contain at least two elements for
 *              the swap to occur.
 *
 * @note After the swap, the second element becomes the new top element,
 *       and the original top element becomes the second element.
 */
static void	swap_stack(t_stack *stack)
{
	t_blist	*first_node;
	t_blist	*second_node;
	t_blist	*third_node;

	if (!stack || !stack->top_element || !stack->top_element->next)
		return ;
	first_node = stack->top_element;
	second_node = first_node->next;
	third_node = second_node->next;
	first_node->next = third_node;
	if (third_node)
		third_node->previous = first_node;
	second_node->next = first_node;
	first_node->previous = second_node;
	second_node->previous = NULL;
	stack->top_element = second_node;
}

void	swap(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a && !stack_b)
	{
		if (stack_a->size < 2)
			ko(stack_a, stack_b);
		swap_stack(stack_a);
	}
	else if (!stack_a && stack_b)
	{
		if (stack_b->size < 2)
			ko(stack_a, stack_b);
		swap_stack(stack_b);
	}
	else if (stack_a && stack_b)
	{
		if (stack_a->size < 2 || stack_b->size < 2)
			ko(stack_a, stack_b);
		swap_stack(stack_a);
		swap_stack(stack_b);
	}
	else
		ko(stack_a, stack_b);
}
