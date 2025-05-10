/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:45:55 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 11:57:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	print_cost(t_cost *cost, t_stack *stack_a)
{
	t_blist	*candidate_node;

	if (!cost)
	{
		printf("Error: Cost calculation failed\n");
		return ;
	}
	candidate_node = get_node_from_index(cost->candidate_index,
			stack_a->top_element);
	printf("\n==== COST CALCULATION RESULTS ====\n");
	printf("Total cost: %d\n", cost->total_cost);
	printf("Candidate index: %d\n", cost->candidate_index);
	if (candidate_node)
		printf("Candidate value: %d\n", candidate_node->value);
	else
		printf("Candidate value: N/A (node not found)\n");
	printf("Stack A movements: %d\n", cost->stack_a_mov);
	printf("Stack B movements: %d\n", cost->stack_b_mov);
	printf("================================\n\n");
}

void	print_stack(t_stack *stack, char stackname)
{
	t_blist	*current;

	if (!stack || !stack->top_element)
	{
		printf("Stack vacío\n");
		return ;
	}
	current = stack->top_element;
	printf("Stack %c: ", stackname);
	while (current)
	{
		printf("%d ", (current->value));
		current = current->next;
	}
	printf("\n");
}
