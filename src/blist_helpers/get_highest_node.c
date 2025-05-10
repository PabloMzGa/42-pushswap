/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_highest_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:09:48 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:32:53 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Find the index of the node with the highest value in a linked list
 *
 * This function traverses the given linked list and identifies the node
 * containing the highest value. It returns the index (position) of this node
 * in the list, with the first node being at index 0.
 *
 * @param lst Pointer to the first node of the linked list to search
 * @return The index of the node with the highest value, or -1 if the list is
 *         empty
 */
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
