/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:40 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 22:04:31 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	clean_stack(t_stack *stack)
{
	t_blist	*element;
	t_blist	*next;

	element = stack->top_element;
	while (element)
	{
		next = element->next;
		ft_free((void **)&(element));
		element = next;
	}
	ft_free((void **)&(stack));
}

/**
 * @brief Cleans up both stack_a and stack_b, prints "KO" to standard output,
 * and exits the program with failure status.
 *
 * This function is typically called when an error or invalid state is
 * detected. It ensures that any allocated memory for the stacks is properly
 * freed before terminating the program.
 *
 * @param stack_a Pointer to the first stack to be cleaned.
 * @param stack_b Pointer to the second stack to be cleaned.
 */
void	ko(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		clean_stack(stack_a);
	if (stack_b)
		clean_stack(stack_b);
	write(STDOUT_FILENO, "KO\n", 3);
	exit(EXIT_FAILURE);
}

void	error(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		clean_stack(stack_a);
	if (stack_b)
		clean_stack(stack_b);
	ft_get_next_line(-1);
	write(STDERR_FILENO, "Error\n", 6);
	exit(EXIT_FAILURE);
}

/**
 * @brief Cleans up both stack_a and stack_b, then prints "OK" to stdout.
 *
 * This function checks if the provided stack pointers are not NULL,
 * and if so, calls clean_stack on each to free their resources.
 * After cleaning, it writes "OK\n" to the standard output.
 *
 * @param stack_a Pointer to the first stack to be cleaned.
 * @param stack_b Pointer to the second stack to be cleaned.
 */
void	ok(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		clean_stack(stack_a);
	if (stack_b)
		clean_stack(stack_b);
	write(STDOUT_FILENO, "OK\n", 3);
}
