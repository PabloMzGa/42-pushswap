/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:09:28 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
			node = create_node(value);
			if (!node)
				error(stack_a, NULL, NULL);
			blstadd_back(&(stack_a->top_element), node);
		}
	}
	return (stack_a->size = i - 1, stack_a);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = parse_num(argc, argv);
	stack_b = initialize_b_stack(stack_a);
	push_b_algo(stack_a, stack_b);
	push_a_algo(stack_a, stack_b);
	clean_stack(stack_a);
	clean_stack(stack_b);
}
