/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lowest_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:09:48 by pablo             #+#    #+#             */
/*   Updated: 2025/05/29 21:34:11 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"


int	get_lowest_node(t_blist *lst)
{
	int	lowest;
	int	i;
	int	selected_i;

	i = 0;
	selected_i = -1;
	lowest = INT_MAX;
	while (lst)
	{
		if (lst->value < lowest)
		{
			lowest = lst->value;
			selected_i = i;
		}
		lst = lst->next;
		++i;
	}
	return (selected_i);
}
