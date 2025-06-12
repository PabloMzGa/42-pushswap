/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_execution_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:48 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/12 21:42:58 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/**
 * @brief Executes stack operations based on instructions from standard input.
 *
 * Reads instructions line by line from STDIN and executes the corresponding
 * stack operation on `stack_a` and `stack_b`. Supported instructions start
 * with 's' (swap), 'p' (push), and 'r' (rotate). On invalid instruction,
 * frees memory, calls the error handler, and exits. Frees memory for each
 * instruction read.
 *
 * @param stack_a Pointer to the first stack.
 * @param stack_b Pointer to the second stack.
 */
void	execute_instructions(t_stack *stack_a, t_stack *stack_b)
{
	char	*instruction;

	instruction = ft_get_next_line(STDIN_FILENO);
	while (instruction && instruction[0] != '\n')
	{
		if (instruction[ft_strlen(instruction) - 2] != '\n')
			error(stack_a, stack_b);
		if (instruction[0] == 's')
			execute_swap(stack_a, stack_b, instruction);
		else if (instruction[0] == 'p')
			execute_push(stack_a, stack_b, instruction);
		else if (instruction[0] == 'r')
			execute_rotations(stack_a, stack_b, instruction);
		else
		{
			ft_free((void **)&instruction);
			error(stack_a, stack_b);
		}
		ft_free((void **)&instruction);
		instruction = ft_get_next_line(STDIN_FILENO);
	}
	if (instruction)
		ft_free((void **)&instruction);
	ft_get_next_line(-1);
}

void	execute_swap(t_stack *stack_a, t_stack *stack_b, char *instruction)
{
	if (instruction[1] == 'a')
		swap(stack_a, NULL);
	else if (instruction[1] == 'b')
		swap(NULL, stack_b);
	else if (instruction[1] == 's')
		swap(stack_a, stack_b);
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}

void	execute_push(t_stack *stack_a, t_stack *stack_b, char *instruction)
{
	if (instruction[1] == 'a')
		push(stack_a, stack_b, 'a');
	else if (instruction[1] == 'b')
		push(stack_a, stack_b, 'b');
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}

void	execute_rotations(t_stack *stack_a, t_stack *stack_b, char *instruction)
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
		else
		{
			ft_free((void **)&instruction);
			error(stack_a, stack_b);
		}
	}
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}
