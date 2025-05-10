/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_mov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:16:58 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:24:29 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	apply_double_rot(t_stack *stack_a, t_stack *stack_b, t_cost *cost)
{
	if (cost->stack_a_mov < 0)
	{
		reverse_rotate(stack_a, stack_b);
		cost->stack_a_mov++;
		cost->stack_b_mov++;
	}
	else
	{
		rotate(stack_a, stack_b);
		cost->stack_a_mov--;
		cost->stack_b_mov--;
	}
}

void	apply_a_rot(t_stack *stack, int *counter)
{
	if (*counter < 0)
	{
		reverse_rotate(stack, NULL);
		(*counter)++;
	}
	else
	{
		rotate(stack, NULL);
		(*counter)--;
	}
}

void	apply_b_rot(t_stack *stack, int *counter)
{
	if (*counter < 0)
	{
		reverse_rotate(NULL, stack);
		(*counter)++;
	}
	else
	{
		rotate(NULL, stack);
		(*counter)--;
	}
}
