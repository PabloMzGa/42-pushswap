/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:40 by pablo             #+#    #+#             */
/*   Updated: 2025/05/08 18:32:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


/**
 * @brief Frees all memory associated with a stack and its elements.
 *
 * This function iterates through all the elements in the stack, freeing
 * the memory allocated for each element's content and the element itself.
 * Finally, it frees the memory allocated for the stack structure.
 *
 * @param stack A pointer to the stack to be cleaned. The stack and all
 *              its elements will be deallocated.
 */
static void	clean_stack(t_stack *stack)
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
void	error(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		clean_stack(stack_a);
	if (stack_b)
		clean_stack(stack_b);
	write(STDERR_FILENO, "Error\n", 6);
	exit(EXIT_FAILURE);
}
