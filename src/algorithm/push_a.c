/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:39 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:33:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	push_a_algo(t_stack *stack_a, t_stack *stack_b)
{
	int index;
	int movements;
	while(stack_b->size > 1)
	{
/* 		print_stack(stack_a, 'a');
		print_stack(stack_b, 'b'); */
		index = get_highest_node(stack_b->top_element);
		movements = get_top_distance(index, stack_b);
		while (movements != 0)
			apply_b_rot(stack_b, &movements);
		push(stack_a, stack_b, 'a');
	}
	push(stack_a, stack_b, 'a');
}
