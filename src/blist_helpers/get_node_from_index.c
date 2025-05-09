/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node_from_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:06:07 by pablo             #+#    #+#             */
/*   Updated: 2025/05/09 20:47:51 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

t_blist	*get_node_from_index(int index, t_blist *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (i == index)
			return (node);
		node = node->next;
		++i;
	}
	return (NULL);
}
