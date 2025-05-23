/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:53:40 by pablo             #+#    #+#             */
/*   Updated: 2025/05/23 13:28:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


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
void	error(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a)
		clean_stack(stack_a);
	if (stack_b)
		clean_stack(stack_b);
	write(STDERR_FILENO, "Error\n", 6);
	exit(EXIT_FAILURE);
}
