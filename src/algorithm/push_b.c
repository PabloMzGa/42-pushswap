/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/06/06 20:34:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sort_3(t_stack *stack)
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

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_a->size > 3 && !is_stack_sorted(stack_a))
	{
		cost = calculate_cost(stack_a, stack_b);
		if (!cost)
			break ;
		while (cost->source_mov || cost->dest_mov)
		{
			if (cost->source_mov > 0 && cost->dest_mov > 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov < 0 && cost->dest_mov < 0)
				apply_double_rot(stack_a, stack_b, cost);
			else if (cost->source_mov != 0)
				apply_a_rot(stack_a, cost, &cost->source_mov);
			else if (cost->dest_mov != 0)
				apply_b_rot(stack_b, cost, &cost->dest_mov);
		}
		push(stack_a, stack_b, cost, 'b');
		ft_free((void **)&cost);
	}
	if (stack_a->size == 3)
		sort_3(stack_a);
}
