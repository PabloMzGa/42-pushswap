/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/05/08 20:55:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_blist	*create_blist_element(int n)
{
	t_blist	*node;

	node = malloc(sizeof(t_blist));
	if (!node)
		return (NULL);
	node->value = n;
	return (node);
}

t_stack	*initialize_stack(int top_value)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top_element = malloc(sizeof(t_blist));
	if (!stack->top_element)
		return (free(stack), NULL);
	stack->top_element->value = top_value;
	return (stack);
}

t_stack	*parse_num(int argc, char *argv[])
{
	int		value;
	int		i;
	t_stack	*stack_a;
	t_blist	*node;

	i = 1;
	stack_a = NULL;
	while (i < argc)
	{
		value = is_arg_correct(argc, argv, i++, stack_a);
		if (i == 2)
		{
			stack_a = initialize_stack(value);
			if (!stack_a)
				return (NULL);
		}
		else
		{
			node = create_blist_element(value);
			if (!node)
				error(stack_a, NULL);
			blstadd_back(&(stack_a->top_element), node);
		}
	}
	return (stack_a->size = i - 1, stack_a);
}

void	print_stack(t_stack *stack)
{
	t_blist	*current;

	if (!stack || !stack->top_element)
	{
		printf("Stack vacío\n");
		return ;
	}
	current = stack->top_element;
	printf("Stack: ");
	while (current)
	{
		printf("%d ", (current->value));
		current = current->next;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = parse_num(argc, argv);
	stack_b = NULL;
	print_stack(stack_a);
}
