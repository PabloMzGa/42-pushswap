/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 20:33:56 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 18:57:29 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	is_stack_sorted(t_stack *stack)
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
