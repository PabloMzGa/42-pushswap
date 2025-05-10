/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_closest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:06 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:42:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	search_closest_high(int n, t_stack *stack)
{
	int		i;
	int		distance;
	int		selected_index;
	t_blist	*current_node;

	distance = INT_MAX;
	i = 0;
	current_node = stack->top_element;
	selected_index = 0;
	while (i < stack->size)
	{
		if (current_node->value > n && current_node->value - n < distance)
		{
			distance = current_node->value - n;
			selected_index = i;
		}
		++i;
		current_node = current_node->next;
	}
	if (distance == INT_MAX)
		return (-1);
	return (selected_index);
}

int	search_closest_low(int n, t_stack *stack)
{
	int		i;
	int		distance;
	int		selected_index;
	t_blist	*current_node;

	distance = INT_MAX;
	i = 0;
	current_node = stack->top_element;
	selected_index = 0;
	while (i < stack->size)
	{
		if (current_node->value < n && n - current_node->value < distance)
		{
			distance = n - current_node->value;
			selected_index = i;
		}
		++i;
		current_node = current_node->next;
	}
	if (distance == INT_MAX)
		return (-1);
	return (selected_index);
}
