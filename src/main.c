/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/05/27 20:21:10 by pablo            ###   ########.fr       */
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
	ft_matrix_free((void **)cleaned_argv, 0);
	stack_b = initialize_b_stack(stack_a);
	push_b_algo(stack_a, stack_b);
	push_a_algo(stack_a, stack_b);
	clean_stack(stack_a);
	clean_stack(stack_b);
}
