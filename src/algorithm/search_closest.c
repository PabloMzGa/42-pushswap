/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_closest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:06 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 20:58:24 by pablo            ###   ########.fr       */
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

int	search_closest_high_global(int value, t_stack *stack_a, t_stack *stack_b)
{
	int		closest_high_a;
	int		closest_high_b;
	int		target_high_value;
	t_blist	*closest_node;

	closest_high_a = search_closest_high(value, stack_a);
	closest_high_b = search_closest_high(value, stack_b);
	target_high_value = INT_MAX;
	if (closest_high_a != -1)
	{
		closest_node = get_node_from_index(closest_high_a,
				stack_a->top_element);
		if (closest_node && closest_node->value < target_high_value)
			target_high_value = closest_node->value;
	}
	if (closest_high_b != -1)
	{
		closest_node = get_node_from_index(closest_high_b,
				stack_b->top_element);
		if (closest_node && closest_node->value < target_high_value)
			target_high_value = closest_node->value;
	}
	return (target_high_value);
}

int	search_closest_low_global(int value, t_stack *stack_a, t_stack *stack_b)
{
	int		closest_low_a;
	int		closest_low_b;
	int		target_low_value;
	t_blist	*closest_node;

	closest_low_a = search_closest_low(value, stack_a);
	closest_low_b = search_closest_low(value, stack_b);
	target_low_value = INT_MIN;
	if (closest_low_a != -1)
	{
		closest_node = get_node_from_index(closest_low_a, stack_a->top_element);
		if (closest_node && closest_node->value > target_low_value)
			target_low_value = closest_node->value;
	}
	if (closest_low_b != -1)
	{
		closest_node = get_node_from_index(closest_low_b, stack_b->top_element);
		if (closest_node && closest_node->value > target_low_value)
			target_low_value = closest_node->value;
	}
	return (target_low_value);
}
