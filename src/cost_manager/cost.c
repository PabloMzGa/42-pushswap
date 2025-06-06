/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:01:24 by pablo             #+#    #+#             */
/*   Updated: 2025/06/06 18:27:15 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Initializes a t_cost structure with default values.
 *
 * This function allocates memory for a t_cost structure and initializes its
 * fields. The total_cost field is set to the maximum possible integer value
 * (INT_MAX). If memory allocation fails, the function calls the error handler
 * and terminates the program.
 *
 * @param source_stack Pointer to the source stack (used for error handling).
 * @param dest_stack Pointer to the destination stack (used for error handling).
 *
 * @return A pointer to the newly allocated and initialized t_cost structure.
 */
static t_cost	*initialize_cost(t_stack *source_stack, t_stack *dest_stack)
{
	t_cost	*cost;

	cost = malloc(sizeof(t_cost));
	if (!cost)
		error(source_stack, dest_stack, NULL);
	cost->total_cost = INT_MAX;
	cost->source_mov = INT_MAX / 2;
	cost->dest_mov = INT_MAX / 2;
	return (cost);
}

/**
 * @brief Compares a new cost with the current minimum cost and updates if lower
 *
 * This function checks if the provided temporary cost is lower than the current
 * total cost stored in the cost structure. If it is, it updates the cost
 * structure with the new values, including the total cost, candidate index, and
 * the number of movements required for both stack A and stack B.
 *
 * @param cost Pointer to a pointer to the cost structure to potentially update
 * @param tmp_cost New cost to compare with the current minimum
 * @param index Index of the element associated with the new cost
 * @param ab_dist Array containing the required movements for stack A [0] and
 *                B [1]
 */
static void	compare_cost(t_cost **cost, int tmp_cost, int index, int ab_dist[])
{
	if (tmp_cost < (*cost)->total_cost)
	{
		(*cost)->total_cost = tmp_cost;
		(*cost)->candidate_index = index;
		(*cost)->source_mov = ab_dist[0];
		(*cost)->dest_mov = ab_dist[1];
	}
}

/**
 * @brief Calculates and sets the optimized move distances and costs.
 *
 * Evaluates two move options based on distances for stack A and B.
 * Calculates the cost for each option using get_optimized_cost.
 * Selects the option with the lower cost, updates ab_dist with the
 * corresponding distances, and returns the minimum cost.
 *
 * @param a_dist Array of two possible distances for stack A.
 * @param b_dist Array of two possible distances for stack B.
 * @param ab_dist Output array for selected optimized distances.
 * @return The minimum cost, or INT_MAX if both options are invalid.
 */
static int	set_optimized_distance(int src_dist[], int dst_dist[],
		int ab_dist[])
{
	int	cost[2];

	if (dst_dist[0] == INT_MAX && dst_dist[1] == INT_MAX)
		return (INT_MAX);
	if (dst_dist[0] != INT_MAX)
		cost[0] = get_optimized_cost(src_dist[0], dst_dist[0]);
	else
		cost[0] = INT_MAX;
	if (dst_dist[1] != INT_MAX)
		cost[1] = get_optimized_cost(src_dist[1], dst_dist[1]);
	else
		cost[1] = INT_MAX;
	if (cost[0] <= cost[1])
	{
		ab_dist[0] = src_dist[0];
		ab_dist[1] = dst_dist[0];
		return (cost[0]);
	}
	else
	{
		ab_dist[0] = src_dist[1];
		ab_dist[1] = dst_dist[1];
		return (cost[1]);
	}
}

/**
 * @brief Calculates the optimized distance for moving an element from the
 *        source stack to the destination stack, considering both normal and
 *        reverse rotations.
 *
 * Computes the distances required to move the element at the given index in
 * the source stack to its position in the destination stack. Evaluates both
 * normal and reverse rotation scenarios for both stacks, and determines the
 * most efficient set of moves. The calculated distances are stored in the
 * provided source_dest_dist array.
 *
 * Array parameters:
 *
 * - src_dist[2]: Stores the distances for moving the element in the source
 *   stack. source_dist[0] is the distance using normal rotation, and
 *   source_dist[1] is the distance using reverse rotation.
 *
 * - dst_dist[2]: Stores the distances for moving the element to its position
 *   in the destination stack. dest_dist[0] is the distance using normal
 *   rotation, and dest_dist[1] is the distance using reverse rotation.
 *
 * - cost[2]: Stores the total move cost for both normal and reverse rotation
 *   scenarios. cost[0] is for normal rotation, and cost[1] is for reverse.
 *
 * @param index            Index of the element in the source stack.
 * @param source_stack     Pointer to the source stack.
 * @param dest_stack       Pointer to the destination stack.
 * @param source_dest_dist Array to store the optimized distances.
 *
 * @return The total cost of the optimized move operation.
 */
static int	get_optimized_source_distance(int index, t_stack *source_stack,
		t_stack *dest_stack, int src_dst_dist[])
{
	int	value;
	int	src_dist[2];
	int	dst_dist[2];

	value = get_node_from_index(index, source_stack->top_element)->value;
	src_dist[0] = get_top_distance(index, source_stack);
	if (src_dist[0] >= 0)
		src_dist[1] = -(source_stack->size - index);
	else
		src_dist[1] = index;
	dst_dist[0] = get_lowest_distance(value, dest_stack, src_dist[0]);
	dst_dist[1] = get_lowest_distance(value, dest_stack, src_dist[1]);
	return (set_optimized_distance(src_dist, dst_dist, src_dst_dist));
}

t_cost	*calculate_cost(t_stack *source_stack, t_stack *dest_stack)
{
	t_cost	*cost;
	int		index;
	int		source_dest_dist[2];
	int		tmp_cost;

	cost = NULL;
	index = 0;
	while (index < source_stack->size)
	{
		if (!cost)
			cost = initialize_cost(source_stack, dest_stack);
		tmp_cost = get_optimized_source_distance(index, source_stack,
				dest_stack, source_dest_dist);
		if (tmp_cost == INT_MAX)
			return (ft_free((void **)&cost), NULL);
		compare_cost(&cost, tmp_cost, index, source_dest_dist);
		++index;
	}
	return (cost);
}
