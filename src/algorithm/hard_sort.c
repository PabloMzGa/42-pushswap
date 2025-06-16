/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:17:28 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/16 13:06:09 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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

void	sort_2(t_stack *stack)
{
	int	n1;
	int	n2;

	n1 = stack->top_element->value;
	n2 = stack->top_element->next->value;
	if (n1 > n2)
		swap(stack, NULL);
}
