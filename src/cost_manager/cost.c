/* ************************************************************************** */
/*                                                 	while (index < stack_a->size)
	{
		value = get_node_from_index(index, stack_a->top_element)->value;
		tmp_cost = get_optimized_a_distance(index, value, stack_a, stack_b,
				ab_dist);
		if (tmp_cost == INT_MAX)
			return (ft_free((void **)&cost), NULL);
		compare_cost(&cost, tmp_cost, index, ab_dist);
		++index;
	}                */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 18:35:16 by pablo            ###   ########.fr       */
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

static int	set_optimized_distance(int a_dist[], int b_dist[], int cost[],
		int ab_dist[])
{
	if (b_dist[0] == INT_MAX && b_dist[1] == INT_MAX)
		return (INT_MAX);
	if (b_dist[0] != INT_MAX)
		cost[0] = get_optimized_cost(a_dist[0], b_dist[0]);
	else
		cost[0] = INT_MAX;
	if (b_dist[1] != INT_MAX)
		cost[1] = get_optimized_cost(a_dist[1], b_dist[1]);
	else
		cost[1] = INT_MAX;
	if (cost[0] <= cost[1])
	{
		ab_dist[0] = a_dist[0];
		ab_dist[1] = b_dist[0];
		return (cost[0]);
	}
	else
	{
		ab_dist[0] = a_dist[1];
		ab_dist[1] = b_dist[1];
		return (cost[1]);
	}
}

static int	get_optimized_source_distance(int index, t_stack *source_stack,
		t_stack *dest_stack, int source_dest_dist[])
{
	int	value;

	int source_dist[2]; // [0]=normal, [1]=reverse
	int dest_dist[2];   // [0]=normal, [1]=reverse
	int cost[2];        // [0]=normal, [1]=reverse
	value = get_node_from_index(index, source_stack->top_element)->value;
	source_dist[0] = get_top_distance(index, source_stack);
	if (source_dist[0] >= 0)
		source_dist[1] = -(source_stack->size - index);
	else
		source_dist[1] = index;
	dest_dist[0] = get_lowest_distance(value, dest_stack, source_dist[0]);
	dest_dist[1] = get_lowest_distance(value, dest_stack, source_dist[1]);
	return (set_optimized_distance(source_dist, dest_dist, cost,
			source_dest_dist));
}

t_cost	*calculate_cost(t_stack *source_stack, t_stack *dest_stack,
		int use_skip_optimization)
{
	t_cost	*cost;
	int		index;
	int		source_dest_dist[2];
	int		tmp_cost;

	cost = NULL;
	index = 0;
	while (index < source_stack->size)
	{
		if (use_skip_optimization && should_skip_element(index, source_stack,
				dest_stack))
		{
			++index;
			continue ;
		}
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
