/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:28:04 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 22:56:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_stack	*initialize_empty_stack(char id)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = NULL;
	stack->size = 0;
	stack->id = id;
	return (stack);
}

t_stack	*initialize_stack(int top_value, char id)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = malloc(sizeof(t_blist));
	if (!stack->top_element)
		return (free(stack), NULL);
	stack->top_element->value = top_value;
	stack->top_element->next = NULL;
	stack->top_element->previous = NULL;
	stack->size = 1;
	stack->id = id;
	return (stack);
}

t_stack	*initialize_b_stack(t_stack *stack_a)
{
	t_stack	*stack_b;

	stack_b = initialize_empty_stack('B');
	push(stack_a, stack_b, NULL, 'b');
	push(stack_a, stack_b, NULL, 'b');
	return (stack_b);
}

t_stack	*populate_a_stack(int argc, char *argv[])
{
	int		value;
	int		i;
	t_stack	*stack_a;
	t_blist	*node;

	if (argc < 2)
		error(NULL,NULL,NULL);
	i = 0;
	stack_a = NULL;
	while (i < argc)
	{
		value = is_arg_correct(argc, argv, i++, stack_a);
		if (i == 1)
		{
			stack_a = initialize_stack(value, 'A');
			if (!stack_a)
				return (NULL);
		}
		else
		{
			node = create_node(value);
			if (!node)
				error(stack_a, NULL, NULL);
			blstadd_back(&(stack_a->top_element), node);
		}
	}
	stack_a->size = i;
	build_expected_order_links(stack_a);
	return (stack_a);
}
