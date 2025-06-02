/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 18:36:27 by pablo            ###   ########.fr       */
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

int	get_lowest_distance(int n, t_stack *stack_b, int a_distance)
{
	int	h_distance;
	int	l_distance;
	int	h_candidate;
	int	l_candidate;

	h_candidate = search_closest_high(n, stack_b);
	l_candidate = search_closest_low(n, stack_b);
	if ((h_candidate == -1 && l_candidate == -1))
		return (INT_MAX);
	h_distance = set_hdistance(h_candidate, stack_b);
	l_distance = set_ldistance(l_candidate, stack_b);
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

	if ((a_mov > 0 && b_mov < 0) || (a_mov < 0 && b_mov > 0))
		cost = abs(a_mov) + abs(b_mov);
	else
	{
		if (abs(a_mov) > abs(b_mov))
			cost = abs(a_mov);
		else
			cost = abs(b_mov);
	}
	return (cost + 1);
}
