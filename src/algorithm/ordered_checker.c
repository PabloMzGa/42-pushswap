/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordered_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:20:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/04 11:48:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Verifies if an element has correct neighbors using pre-calculated
 *        expected links
 *
 * This function checks if a node has at least one neighbor (previous or next)
 * that matches the expected order using O(1) pointer comparisons instead of
 * expensive searches. This helps preserve already ordered subsequences during
 * push_b phase.
 *
 * @param node Pointer to the node to check
 * @param stack_a Pointer to stack A (unused, kept for compatibility)
 * @param stack_b Pointer to stack B (unused, kept for compatibility)
 * @return 1 if the element is well positioned, 0 otherwise
 */
static int	is_element_ordered(t_blist *node)
{
	if (!node)
		return (0);
	if (node->next && node->expected_next && node->next == node->expected_next)
		return (1);
	if (node->previous && node->expected_prev
		&& node->previous == node->expected_prev)
		return (1);
	return (0);
}

/**
 * @brief Checks if an element should be skipped during push_b phase
 *
 * This function determines if an element at the given index should be
 * skipped (not pushed to stack_b) because it's already well positioned
 * in a subsequence, considering elements in both stacks.
 *
 * @param index Index of the element to check in stack_a
 * @param stack_a Pointer to stack A containing the element
 * @param stack_b Pointer to stack B (may contain related elements)
 * @return 1 if element should be skipped, 0 if it should be processed
 */
int	should_skip_element(int index, t_stack *stack)
{
	t_blist	*node;

	node = get_node_from_index(index, stack->top_element);
	if (!node)
		return (0);
	return (is_element_ordered(node));
}
