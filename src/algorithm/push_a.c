/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:25:36 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	int	index;
	int	movements;

	while (stack_b->size > 1)
	{
		index = get_highest_node(stack_b->top_element);
		movements = get_top_distance(index, stack_b);
		while (movements != 0)
			apply_b_rot(stack_b, NULL, &movements);
		push(stack_a, stack_b, NULL, 'a');
	}
	push(stack_a, stack_b, NULL, 'a');
}
