/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:34:34 by pablo             #+#    #+#             */
/*   Updated: 2025/06/07 13:36:36 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	execute_instructions(t_stack *stack_a, t_stack *stack_b)
{
	char	*instruction;

	instruction = ft_get_next_line(STDIN_FILENO);
	while (instruction[0] != '\n')
	{
		if (instruction[0] == 's')
		{
			if (instruction[1] == 'a')
				swap(stack_a, NULL);
			else if (instruction[1] == 'b')
				swap(NULL, stack_b);
			else if (instruction[1] == 's')
				swap(stack_a, stack_b);
		}
		else if (instruction[0] == 'p')
		{
			if (instruction[1] == 'a')
				push(stack_a, stack_b, 'a');
			else if (instruction[1] == 'b')
				push(stack_a, stack_b, 'b');
		}
		else if (instruction[0] == 'r')
		{
			if (instruction[1] == 'a')
				rotate(stack_a, NULL);
			else if (instruction[1] == 'b')
				rotate(NULL, stack_b);
			else if (instruction[1] == 'r')
			{
				if (instruction[2] == '\n')
					rotate(stack_a, stack_b);
				else if (instruction[2] == 'a')
					reverse_rotate(stack_a, NULL);
				else if (instruction[2] == 'b')
					reverse_rotate(NULL, stack_b);
				else if (instruction[2] == 'r')
					reverse_rotate(stack_a, stack_b);
			}
		}
		ft_free((void **)&instruction);
		instruction = ft_get_next_line(STDIN_FILENO);
	}
}

int	main(int argc, char *argv[])
{
	char	**cleaned_argv;
	t_stack	*stack_a;
	t_stack	*stack_b;

	cleaned_argv = clean_argv(argc, argv);
	stack_a = populate_a_stack(ft_matrix_len((void **)cleaned_argv),
			cleaned_argv);
	stack_b = initialize_empty_stack('B');
	execute_instructions(stack_a, stack_b);

	if (stack_b->size == 0 && is_stack_sorted(stack_a))
		return (ok(stack_a, stack_b), 0);
	else
		ko(stack_a, stack_b);
}
