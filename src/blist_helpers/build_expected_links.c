/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expected_links.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:05:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 22:14:41 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Builds expected order links for optimization
 *
 * This function creates the expected_prev and expected_next links for all
 * nodes in the given stack. These links point to the nodes that should
 * come immediately before and after each node in the final sorted order.
 * This uses the existing search_closest_low and search_closest_high functions
 * to identify the correct neighbors for each node.
 *
 * @param stack_a Pointer to stack A containing all the nodes to process
 */
void	build_expected_order_links(t_stack *stack_a)
{
	t_blist	*current;
	int		closest_low_index;
	int		closest_high_index;

	current = stack_a->top_element;
	while (current)
	{
		// Find the node with the highest value that is still lower than current
		closest_low_index = search_closest_low(current->value, stack_a);
		if (closest_low_index != -1)
			current->expected_prev = get_node_from_index(closest_low_index, stack_a->top_element);
		else
			current->expected_prev = NULL;

		// Find the node with the lowest value that is still higher than current
		closest_high_index = search_closest_high(current->value, stack_a);
		if (closest_high_index != -1)
			current->expected_next = get_node_from_index(closest_high_index, stack_a->top_element);
		else
			current->expected_next = NULL;

		current = current->next;
	}
}
