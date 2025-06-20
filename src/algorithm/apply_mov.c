/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:16:58 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 22:14:45 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	apply_double_rot(t_stack *stack_a, t_stack *stack_b, t_cost *cost)
{
	if (cost->source_mov < 0)
	{
		reverse_rotate(stack_a, stack_b, cost);
		cost->source_mov++;
		cost->dest_mov++;
	}
	else
	{
		rotate(stack_a, stack_b, cost);
		cost->source_mov--;
		cost->dest_mov--;
	}
}

void	apply_a_rot(t_stack *stack, t_cost *cost, int *counter)
{
	if (*counter < 0)
	{
		reverse_rotate(stack, NULL, cost);
		(*counter)++;
	}
	else
	{
		rotate(stack, NULL, cost);
		(*counter)--;
	}
}

void	apply_b_rot(t_stack *stack, t_cost *cost, int *counter)
{
	if (*counter < 0)
	{
		reverse_rotate(NULL, stack, cost);
		(*counter)++;
	}
	else
	{
		rotate(NULL, stack, cost);
		(*counter)--;
	}
}
