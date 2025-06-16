/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_execution_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:58:48 by pabmart2          #+#    #+#             */
/*   Updated: 2025/06/16 13:06:00 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/**
 * @brief Executes the appropriate swap operation on the given stacks based on
 *        the instruction.
 *
 * Compares the instruction string to determine which swap operation to perform:
 * - "sa\n": Swaps the top two elements of stack_a.
 * - "sb\n": Swaps the top two elements of stack_b.
 * - "ss\n": Swaps the top two elements of both stack_a and stack_b.
 * If the instruction does not match any of the above, it frees the instruction
 * and calls the error handler.
 *
 * @param stack_a Pointer to the first stack (t_stack).
 * @param stack_b Pointer to the second stack (t_stack).
 * @param instruction The instruction string indicating which swap operation to
 *        execute.
 */
static void	execute_swap(t_stack *stack_a, t_stack *stack_b, char *instruction)
{
	if (!ft_strncmp(instruction, "sa\n", 3))
		swap(stack_a, NULL);
	else if (!ft_strncmp(instruction, "sb\n", 3))
		swap(NULL, stack_b);
	else if (!ft_strncmp(instruction, "ss\n", 3))
		swap(stack_a, stack_b);
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}

/**
 * @brief Executes a push operation on the given stacks based on the
 *        instruction.
 *
 * This function checks the provided instruction string and performs the
 * corresponding push operation between stack_a and stack_b. If the
 * instruction is "pa\n", it pushes the top element from stack_b to
 * stack_a. If the instruction is "pb\n", it pushes the top element from
 * stack_a to stack_b. If the instruction is invalid, it frees the
 * instruction memory and calls the error handler.
 *
 * @param stack_a Pointer to the first stack (t_stack).
 * @param stack_b Pointer to the second stack (t_stack).
 * @param instruction The instruction string to execute ("pa\n" or "pb\n").
 */
static void	execute_push(t_stack *stack_a, t_stack *stack_b, char *instruction)
{
	if (!ft_strncmp(instruction, "pa\n", 3))
		push(stack_a, stack_b, 'a', instruction);
	else if (!ft_strncmp(instruction, "pb\n", 3))
		push(stack_a, stack_b, 'b', instruction);
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}

/**
 * @brief Executes rotation or reverse rotation operations on the given stacks
 *        based on the provided instruction string.
 *
 * This function interprets the instruction string and applies the corresponding
 * rotation or reverse rotation operation to stack_a, stack_b, or both. If the
 * instruction does not match any known operation, it frees the instruction and
 * triggers an error handler.
 *
 * @param stack_a Pointer to the first stack (t_stack).
 * @param stack_b Pointer to the second stack (t_stack).
 * @param instruction String containing the operation to execute
 * (e.g., "ra\n", "rrr\n").
 */
static void	execute_rotations(t_stack *stack_a, t_stack *stack_b,
		char *instruction)
{
	if (!ft_strncmp(instruction, "ra\n", 3))
		rotate(stack_a, NULL);
	else if (!ft_strncmp(instruction, "rb\n", 3))
		rotate(NULL, stack_b);
	else if (!ft_strncmp(instruction, "rr\n", 3))
		rotate(stack_a, stack_b);
	else if (!ft_strncmp(instruction, "rra\n", 4))
		reverse_rotate(stack_a, NULL);
	else if (!ft_strncmp(instruction, "rrb\n", 4))
		reverse_rotate(NULL, stack_b);
	else if (!ft_strncmp(instruction, "rrr\n", 4))
		reverse_rotate(stack_a, stack_b);
	else
	{
		ft_free((void **)&instruction);
		error(stack_a, stack_b);
	}
}

void	execute_instructions(t_stack *stack_a, t_stack *stack_b)
{
	char	*instruction;

	instruction = ft_get_next_line(STDIN_FILENO);
	while (instruction && instruction[0] != '\n')
	{
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
