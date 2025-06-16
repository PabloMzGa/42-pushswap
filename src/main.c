/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/06/16 13:06:13 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Creates and initializes stack_a from command-line arguments.
 *
 * This function processes the command-line arguments, cleans them using
 * clean_argv(), and then populates stack_a with the resulting values.
 * It also handles memory management for the cleaned arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return A pointer to the initialized t_stack structure representing stack_a.
 *         If memory allocation or argument cleaning fails, the function
 *         calls error() and does not return normally.
 */
static t_stack	*create_stack_a(int argc, char *argv[])
{
	t_stack	*stack_a;
	char	**cleaned_argv;

	cleaned_argv = clean_argv(argc, argv);
	if (!cleaned_argv)
		error(NULL, NULL, NULL);
	stack_a = populate_a_stack(ft_matrix_len((void **)cleaned_argv),
			cleaned_argv);
	ft_matrix_free((void ***)&cleaned_argv, 0);
	return (stack_a);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = create_stack_a(argc, argv);
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
	else if (stack_a->size == 3)
		sort_3(stack_a);
	else if (stack_a->size == 2)
		sort_2(stack_a);
	return (clean_stack(stack_a), 0);
}
