/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/06/06 18:00:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Calculates the distance for a given low candidate in the stack
 *
 * This function determines the distance from the candidate to the bottom of
 * the stack. If the candidate is invalid (-1), it returns INT_MAX to indicate
 * an infinite or maximum distance.
 *
 * @param candidate The index or position to calculate distance for
 * @param stack Pointer to the stack structure
 * @return The horizontal distance to the bottom, or INT_MAX if candidate is -1.
 *         A negative distance means the rotation needs to be in reverse.
 */
static int	set_ldistance(int candidate, t_stack *stack)
{
	if (candidate != -1)
		return (get_top_distance(candidate, stack));
	else
		return (INT_MAX);
}

/**
 * @brief Calculates the distance for a given high candidate in the stack
 *
 * This function determines the distance from the candidate to the bottom of
 * the stack. If the candidate is invalid (-1), it returns INT_MAX to indicate
 * an infinite or maximum distance.
 *
 * @param candidate The index or position to calculate distance for
 * @param stack Pointer to the stack structure
 * @return The horizontal distance to the bottom, or INT_MAX if candidate is -1.
 *         A negative distance means the rotation needs to be in reverse.
 */
static int	set_hdistance(int candidate, t_stack *stack)
{
	if (candidate != -1)
		return (get_bottom_distance(candidate, stack));
	else
		return (INT_MAX);
}

/**
 * @brief Sets the high and low candidate values for a given number and
 * destination stack.
 *
 * Depending on the id of the destination stack, this function assigns the
 * closest high and low candidates to the provided pointers. If the stack id
 * is 'B', it searches for the closest high and low values relative to n in
 * the destination stack. Otherwise, it reverses the assignment.
 *
 * @param h_candidate Pointer to store the high candidate value.
 * @param l_candidate Pointer to store the low candidate value.
 * @param n The reference number to compare against stack elements.
 * @param dst_stack Pointer to the destination stack structure.
 */
static void	set_hl_candidate(int *h_candidate, int *l_candidate, int n,
		t_stack *dst_stack)
{
	if (dst_stack->id == 'B')
	{
		*h_candidate = search_closest_high(n, dst_stack);
		*l_candidate = search_closest_low(n, dst_stack);
	}
	else
	{
		*h_candidate = search_closest_low(n, dst_stack);
		*l_candidate = search_closest_high(n, dst_stack);
	}
}

int	get_lowest_distance(int n, t_stack *dst_stack, int a_distance)
{
	int	h_distance;
	int	l_distance;
	int	h_candidate;
	int	l_candidate;

	set_hl_candidate(&h_candidate, &l_candidate, n, dst_stack);
	if ((h_candidate == -1 && l_candidate == -1))
		return (INT_MAX);
	h_distance = set_hdistance(h_candidate, dst_stack);
	l_distance = set_ldistance(l_candidate, dst_stack);
	if (h_distance == INT_MAX && l_distance != INT_MAX)
		return (l_distance);
	else if (h_distance != INT_MAX && l_distance == INT_MAX)
		return (h_distance);
	else if (h_distance == INT_MAX && l_distance == INT_MAX)
		return (INT_MAX);
	else if (get_optimized_cost(a_distance,
			h_distance) < get_optimized_cost(a_distance, l_distance))
		return (h_distance);
	else
		return (l_distance);
}

int	get_optimized_cost(int a_mov, int b_mov)
{
	int	cost;
	int	abs_a;
	int	abs_b;

	abs_a = abs(a_mov);
	abs_b = abs(b_mov);
	if ((a_mov > 0 && b_mov < 0) || (a_mov < 0 && b_mov > 0))
		cost = abs_a + abs_b;
	else
	{
		if (abs_a > abs_b)
			cost = abs_a;
		else
			cost = abs_b;
	}
	return (cost + 1);
}
