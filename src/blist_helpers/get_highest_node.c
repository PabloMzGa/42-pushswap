/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_highest_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:09:48 by pablo             #+#    #+#             */
/*   Updated: 2025/06/06 18:27:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	get_highest_node(t_blist *lst)
{
	int	higher;
	int	i;
	int	selected_i;

	i = 0;
	selected_i = -1;
	higher = INT_MIN;
	while (lst)
	{
		if (lst->value > higher)
		{
			higher = lst->value;
			selected_i = i;
		}
		lst = lst->next;
		++i;
	}
	return (selected_i);
}
