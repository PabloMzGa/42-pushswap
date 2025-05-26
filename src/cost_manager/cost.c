/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:24:52 by pabmart2         ###   ########.fr       */
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
	return (cost);
}

static void	compare_cost(t_cost **cost, int tmp_cost, int index, int ab_dist[])
{
	if (tmp_cost < (*cost)->total_cost)
	{
		(*cost)->total_cost = tmp_cost;
		(*cost)->candidate_index = index;
		(*cost)->stack_a_mov = ab_dist[0];
		(*cost)->stack_b_mov = ab_dist[1];
	}
}

t_cost	*calculate_cost(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;
	int		index;
	int		ab_dist[2];
	int		tmp_cost;

	cost = initialize_cost(stack_a, stack_b);
	index = 0;
	while (index < stack_a->size)
	{
		ab_dist[0] = get_top_distance(index, stack_a);
		ab_dist[1] = get_lowest_distance(get_node_from_index(index,
					stack_a->top_element)->value, stack_b, ab_dist[0]);
		if (ab_dist[1] == INT_MAX)
			return (ft_free((void **)&cost), NULL);
		tmp_cost = get_optimized_cost(ab_dist[0], ab_dist[1]);
		++index;
	}
	compare_cost(&cost, tmp_cost, index, ab_dist);
	return (cost);
}
