/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lowest_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:15:00 by pablo             #+#    #+#             */
/*   Updated: 2025/06/02 20:57:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	get_lowest_node(t_blist *lst)
{
	int	lower;
	int	i;
	int	selected_i;

	i = 0;
	selected_i = -1;
	lower = INT_MAX;
	while (lst)
	{
		if (lst->value < lower)
		{
			lower = lst->value;
			selected_i = i;
		}
		lst = lst->next;
		++i;
	}
	return (selected_i);
}
