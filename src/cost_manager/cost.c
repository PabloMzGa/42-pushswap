/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 14:02:05 by pablo            ###   ########.fr       */
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
		error(stack_a, stack_b);
	cost->total_cost = INT_MAX;
	return (cost);
}

/**
 * TODO: En caso de empate entre subir o bajar B, tendría
 * que comprobar si A tiene que subir o bajar, para aprovechar
 * los dobles.
 */
static void	search_top(t_cost **cost, t_stack *stack_a, t_stack *stack_b)
{
	int	index;
	int	b_distance;
	int	a_distance;
	int	tmp_cost;

	index = 0;
	while (index < cost_depth && index < stack_a->size)
	{
		a_distance = get_top_distance(index, stack_a);
		b_distance = get_lowest_distance(get_node_from_index(index,
					stack_a->top_element)->value, stack_a, stack_b, a_distance);
		tmp_cost = get_optimized_cost(a_distance, b_distance);
		if (tmp_cost < (*cost)->total_cost)
		{
			(*cost)->total_cost = tmp_cost;
			(*cost)->candidate_index = index;
			(*cost)->stack_a_mov = a_distance;
			(*cost)->stack_b_mov = b_distance;
		}
		++index;
	}
}

static void	search_bottom(t_cost **cost, t_stack *stack_a, t_stack *stack_b)
{
	int	index;
	int	b_distance;
	int	a_distance;
	int	tmp_cost;

	index = stack_a->size - 1;
	while (stack_a->size - cost_depth > 0 && index > stack_a->size - cost_depth)
	{
		a_distance = get_top_distance(index, stack_a);
		b_distance = get_lowest_distance(get_node_from_index(index,
					stack_a->top_element)->value, stack_a, stack_b, a_distance);
		tmp_cost = get_optimized_cost(a_distance, b_distance);
		if (tmp_cost < (*cost)->total_cost)
		{
			(*cost)->total_cost = tmp_cost;
			(*cost)->candidate_index = index;
			(*cost)->stack_a_mov = a_distance;
			(*cost)->stack_b_mov = b_distance;
		}
		--index;
	}
}

t_cost	*calculate_cost(t_stack *stack_a, t_stack *stack_b)
{
	t_cost	*cost;

	cost = initialize_cost(stack_a, stack_b);
	search_top(&cost, stack_a, stack_b);
	search_bottom(&cost, stack_a, stack_b);
	return (cost);
}
