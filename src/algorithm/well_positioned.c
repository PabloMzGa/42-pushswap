/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   well_positioned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:20:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 20:30:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Checks if the given node in a doubly linked list has its next neighbor
 * with the correct target value according to the stacks provided.
 *
 * This function determines the "target high value" for the current node's value
 * using the provided stack_a and stack_b. If the target value is found and the
 * node has a next neighbor, it checks if the next neighbor's value matches the
 * target value.
 *
 * @param node      Pointer to the current node in the blist.
 * @param stack_a   Pointer to stack A, used for target value calculation.
 * @param stack_b   Pointer to stack B, used for target value calculation.
 *
 * @return          1 if the next neighbor's value matches the target high
 *                  value, 0 otherwise (including if no next neighbor or no
 *                  valid target).
 */
static int	has_correct_next_neighbor(t_blist *node, t_stack *stack_a,
		t_stack *stack_b)
{
	int	target_high_value;

	target_high_value = search_closest_high_global(node->value, stack_a, stack_b);
	if (target_high_value == INT_MAX)
		return (0);
	if (!node->next)
		return (0);
	return (node->next->value == target_high_value);
}

/**
 * @brief Checks if the given node in a doubly linked list has its previous
 * neighbor with the correct target value according to the stacks provided.
 *
 * This function determines the "target low value" for the current node's value
 * using the provided stack_a and stack_b. If the target value is found and the
 * node has a previous neighbor, it checks if the previous neighbor's value
 * matches the target value.
 * @param node      Pointer to the current node in the blist.
 * @param stack_a   Pointer to stack A, used for target value calculation.
 * @param stack_b   Pointer to stack B, used for target value calculation.
 *
 * @return          1 if the next neighbor's value matches the target high
 *                  value, 0 otherwise (including if no next neighbor or no
 *                  valid target).
 */
static int	has_correct_prev_neighbor(t_blist *node, t_stack *stack_a,
		t_stack *stack_b)
{
	int	target_low_value;

	target_low_value = search_closest_low_global(node->value, stack_a, stack_b);
	if (target_low_value == INT_MIN)
		return (0);
	if (!node->previous)
		return (0);
	return (node->previous->value == target_low_value);
}

/**

	* @brief Verifies if an element has correct global neighbors using search_closest
 *
 * This function checks if a node has at least one neighbor (previous or next)
 * that matches what search_closest_high or search_closest_low would return
 * when considering BOTH stacks (since elements may be distributed).
 * This helps preserve already ordered subsequences during push_b phase.
 *
 * @param node Pointer to the node to check
 * @param stack_a Pointer to stack A
 * @param stack_b Pointer to stack B
 * @return 1 if the element is well positioned, 0 otherwise
 */
static int	is_element_well_positioned(t_blist *node, t_stack *stack_a,
		t_stack *stack_b)
{
	if (!node)
		return (0);
	if (has_correct_next_neighbor(node, stack_a, stack_b))
		return (1);
	return (has_correct_prev_neighbor(node, stack_a, stack_b));
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
int	should_skip_element(int index, t_stack *stack_a, t_stack *stack_b)
{
	t_blist	*node;

	node = get_node_from_index(index, stack_a->top_element);
	if (!node)
		return (0);
	return (is_element_well_positioned(node, stack_a, stack_b));
}
