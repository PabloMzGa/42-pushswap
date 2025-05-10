/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:54:05 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 02:09:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Applies rotation to both stacks simultaneously based on movement cost
 *
 * This function optimizes stack operations by performing simultaneous rotations
 * on both stacks when possible. Depending on the sign of stack_a_mov in the
 * cost structure, it either:
 *
 * - Performs reverse rotation on both stacks if movement is negative
 *
 * - Performs forward rotation on both stacks if movement is positive
 *
 * After each operation, it updates the movement counters in the cost structure.
 *
 * @param stack_a Pointer to the first stack
 * @param stack_b Pointer to the second stack
 * @param cost Pointer to cost structure containing movement information
 */
static void	apply_rr(t_stack *stack_a, t_stack *stack_b, t_cost *cost)
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

/**
 * @brief Applies a single rotation move to the stack based on counter sign
 *
 * This function performs either a rotate or reverse_rotate operation on the
 * stack depending on the sign of the counter. After the operation, the counter
 * is adjusted accordingly.
 *
 * @param stack Pointer to the stack to manipulate
 * @param counter Pointer to counter determining direction and tracking
 *                operations:
 *                - If negative: performs reverse_rotate and increments counter
 *                - If positive/zero: performs rotate and decrements counter
 */
static void	apply_single_move(t_stack *stack, int *counter)
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

void	push_b_algo(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	while (stack_a->size > 0)
	{
		cost = calculate_cost(stack_a, stack_b);
		while (cost->stack_a_mov || cost->stack_b_mov)
		{
			if (cost->stack_a_mov > 0 && cost->stack_b_mov > 0)
				apply_rr(stack_a, stack_b, cost);
			else if (cost->stack_a_mov < 0 && cost->stack_b_mov < 0)
				apply_rr(stack_a, stack_b, cost);
			else if (cost->stack_a_mov != 0)
				apply_single_move(stack_a, &cost->stack_a_mov);
			else if (cost->stack_b_mov != 0)
				apply_single_move(stack_b, &cost->stack_b_mov);
		}
		push(stack_a, stack_b, 'b');
		free(cost);
	}
}
