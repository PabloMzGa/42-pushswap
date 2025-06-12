/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:17:28 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/12 21:44:53 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Sorts the top three elements of the given stack in ascending order.
 *
 * This function assumes that the stack contains at least three elements.
 * It compares the values of the top three elements and applies the minimal
 * sequence of stack operations (swap, rotate, reverse rotate) to sort them.
 * If the elements are already sorted, the function does nothing.
 *
 * @param stack Pointer to the stack to be sorted.
 */
void	sort_3(t_stack *stack)
{
	int	n1;
	int	n2;
	int	n3;

	n1 = stack->top_element->value;
	n2 = stack->top_element->next->value;
	n3 = stack->top_element->next->next->value;
	if (n1 < n2 && n2 < n3)
		return ;
	else if (n1 < n2 && n1 < n3 && n2 > n3)
	{
		reverse_rotate(stack, NULL, NULL);
		swap(stack, NULL);
	}
	else if (n1 > n2 && n1 < n3 && n2 < n3)
		swap(stack, NULL);
	else if (n1 < n2 && n1 > n3 && n2 > n3)
		reverse_rotate(stack, NULL, NULL);
	else if (n1 > n2 && n1 > n3 && n2 < n3)
		rotate(stack, NULL, NULL);
	else if (n1 > n2 && n1 > n3 && n2 > n3)
	{
		rotate(stack, NULL, NULL);
		swap(stack, NULL);
	}
}
