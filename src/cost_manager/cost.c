/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/05/28 17:54:43 by pablo            ###   ########.fr       */
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
 * @param stack_a Pointer to the first stack (used for error handling).
 * @param stack_b Pointer to the second stack (used for error handling).
 *
 * @return A pointer to the newly allocated and initialized t_cost structure.
 */
static t_cost	*initialize_cost(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	cost = malloc(sizeof(t_cost));
	if (!cost)
		error(stack_a, stack_b, NULL);
	cost->total_cost = INT_MAX;
	cost->stack_a_mov = INT_MAX / 2;
	cost->stack_b_mov = INT_MAX / 2;
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
	if (tmp_cost <= (*cost)->total_cost)
	{
		(*cost)->total_cost = tmp_cost;
		(*cost)->candidate_index = index;
		(*cost)->stack_a_mov = ab_dist[0];
		(*cost)->stack_b_mov = ab_dist[1];
	}
}

/* int	is_inside_chunk(int value, int current_chunk)
{
	if (current_chunk == 0 && value >= 0 && value < 100)
		return (1);
	else if (current_chunk == 1 && value >= 100 && value < 200)
		return (1);
	else if (current_chunk == 2 && value >= 200 && value < 300)
		return (1);
	else if (current_chunk == 3 && value >= 300 && value < 400)
		return (1);
	else if (current_chunk == 4 && value >= 400 && value < 501)
		return (1);
	else
		return (0);
} */

t_cost	*calculate_cost(t_stack *stack_a, t_stack *stack_b, int current_chunk)
{
	t_cost	*cost;
	int		index;
	int		ab_dist[2];
	int		tmp_cost;
	int		value;

	(void)current_chunk;
	cost = initialize_cost(stack_a, stack_b);
	index = 0;
	while (index < stack_a->size)
	{
		value = get_node_from_index(index, stack_a->top_element)->value;
/* 		if (!is_inside_chunk(value, current_chunk))
		{
			++index;
			continue ;
		} */
		ab_dist[0] = get_top_distance(index, stack_a);
		ab_dist[1] = get_lowest_distance(value, stack_b, ab_dist[0]);
		if (ab_dist[1] == INT_MAX)
			return (ft_free((void **)&cost), NULL);
		tmp_cost = get_optimized_cost(ab_dist[0], ab_dist[1]);
		compare_cost(&cost, tmp_cost, index, ab_dist);
		++index;
	}
	return (cost);
}
