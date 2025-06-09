/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:34:34 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 22:03:02 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"


int	main(int argc, char *argv[])
{
	char	**cleaned_argv;
	t_stack	*stack_a;
	t_stack	*stack_b;

	cleaned_argv = clean_argv(argc, argv);
	stack_a = populate_a_stack(ft_matrix_len((void **)cleaned_argv),
			cleaned_argv);
	ft_matrix_free((void ***)&cleaned_argv, 0);
	stack_b = initialize_empty_stack('B');
	execute_instructions(stack_a, stack_b);
	if (stack_b->size == 0 && is_stack_sorted(stack_a))
		return (ok(stack_a, stack_b), 0);
	else
		ko(stack_a, stack_b);
}
