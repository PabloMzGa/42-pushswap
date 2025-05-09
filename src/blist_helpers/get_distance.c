/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:06:07 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 00:25:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	get_top_distance(int index, t_stack *stack)
{
	if (stack->size / 2 >= index)
		return (index);
	else
		return (-(stack->size - index));
}

int	get_bottom_distance(int index, t_stack *stack)
{
	if (stack->size / 2 < index)
		return (stack->size - index - 1);
	else
		return (-(stack->size - index - 1));
}
