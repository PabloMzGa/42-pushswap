/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:57:56 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 14:23:56 by pablo            ###   ########.fr       */
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
	cost->src_stack_mov = INT_MAX / 2;
	cost->dst_stack_mov = INT_MAX / 2;
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
		(*cost)->src_stack_mov = ab_dist[0];
		(*cost)->dst_stack_mov = ab_dist[1];
	}
}

static int	is_ordered_forward(int index, t_stack *current_stack,
		t_stack *other_stack)
{
	int	current_value;
	int	expected_next_index;
	int	closest_high_other;
	int	next_index;
	int	closest_value_current;
	int	closest_value_other;

	if (current_stack->size <= 1)
		return (1);
	current_value = get_node_from_index(index,
			current_stack->top_element)->value;
	expected_next_index = search_closest_high(current_value, current_stack);
	closest_high_other = search_closest_high(current_value, other_stack);
	// Si hay un elemento más cercano en el otro stack, no está ordenado
	if (closest_high_other != -1 && expected_next_index != -1)
	{
		closest_value_current = get_node_from_index(expected_next_index,
				current_stack->top_element)->value;
		closest_value_other = get_node_from_index(closest_high_other,
				other_stack->top_element)->value;
		if (closest_value_other < closest_value_current)
			return (0);
	}
	else if (closest_high_other != -1 && expected_next_index == -1)
		return (0);
	// Si no hay elemento mayor, verificar si está en última posición
	if (expected_next_index == -1)
		return (index == current_stack->size - 1);
	// Verificar si el siguiente en posición coincide con el esperado
	if (index == current_stack->size - 1)
		next_index = 0;
	else
		next_index = index + 1;
	return (next_index == expected_next_index);
}

static int	is_ordered_backward(int index, t_stack *current_stack,
		t_stack *other_stack)
{
	int	current_value;
	int	expected_prev_index;
	int	closest_low_other;
	int	prev_index;
	int	closest_value_current;
	int	closest_value_other;

	if (current_stack->size <= 1)
		return (1);
	current_value = get_node_from_index(index,
			current_stack->top_element)->value;
	expected_prev_index = search_closest_low(current_value, current_stack);
	closest_low_other = search_closest_low(current_value, other_stack);
	// Si hay un elemento más cercano en el otro stack, no está ordenado
	if (closest_low_other != -1 && expected_prev_index != -1)
	{
		closest_value_current = get_node_from_index(expected_prev_index,
				current_stack->top_element)->value;
		closest_value_other = get_node_from_index(closest_low_other,
				other_stack->top_element)->value;
		if (closest_value_other > closest_value_current)
			return (0);
	}
	else if (closest_low_other != -1 && expected_prev_index == -1)
		return (0);
	// Si no hay elemento menor, verificar si está en primera posición
	if (expected_prev_index == -1)
		return (index == 0);
	// Verificar si el anterior en posición coincide con el esperado
	if (index == 0)
		prev_index = current_stack->size - 1;
	else
		prev_index = index - 1;
	return (prev_index == expected_prev_index);
}

/**
 * @brief Checks if an element is properly ordered in both directions.
 *
 * This function combines the forward and backward ordering checks to determine
 * if an element is correctly positioned relative to both its predecessor and
 * successor in the sorted sequence.
 *
 * @param index The index of the element to check in the current stack
 * @param current_stack The stack containing the element to verify
 * @param other_stack The other stack to check for closer values
 * @return 1 if the element is ordered in both directions, 0 otherwise
 */
static int	is_ordered(int index, t_stack *current_stack, t_stack *other_stack)
{
	int	forward;
	int	backward;

	forward = is_ordered_forward(index, current_stack, other_stack);
	backward = is_ordered_backward(index, current_stack, other_stack);
	return (forward || backward);
}

t_cost	*calculate_cost(t_stack *src_stack, t_stack *dst_stack, int check_order)
{
	t_cost	*cost;
	int		index;
	int		ab_dist[2];

	cost = NULL;
	index = 0;
	while (index < src_stack->size)
	{
		if (!check_order || !is_ordered(index, src_stack, dst_stack))
		{
			if (!cost)
				cost = initialize_cost(src_stack, dst_stack);
			ab_dist[0] = get_top_distance(index, src_stack);
			ab_dist[1] = get_lowest_distance(get_node_from_index(index,
						src_stack->top_element)->value, dst_stack, ab_dist[0]);
			if (ab_dist[1] == INT_MAX)
				return (ft_free((void **)&cost), NULL);
			compare_cost(&cost, get_optimized_cost(ab_dist[0], ab_dist[1]),
				index, ab_dist);
		}
		++index;
	}
	return (cost);
}
