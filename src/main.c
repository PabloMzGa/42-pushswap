/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/06/12 21:44:04 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**cleaned_argv;

	cleaned_argv = clean_argv(argc, argv);
	if (!cleaned_argv)
		error(NULL, NULL, NULL);
	stack_a = populate_a_stack(ft_matrix_len((void **)cleaned_argv),
			cleaned_argv);
	ft_matrix_free((void ***)&cleaned_argv, 0);
	if (is_stack_sorted(stack_a))
		return (clean_stack(stack_a), 0);
	if (stack_a->size > 3)
	{
		stack_b = initialize_b_stack(stack_a);
		if (!stack_b)
			error(stack_a, NULL, NULL);
		push_b_algo(stack_a, stack_b);
		push_a_algo(stack_a, stack_b);
		clean_stack(stack_b);
	}
	else
		sort_3(stack_a);
	return (clean_stack(stack_a), 0);
}
