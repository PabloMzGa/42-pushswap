/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:48:57 by pablo             #+#    #+#             */
/*   Updated: 2025/05/09 12:50:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Retrieves the last node in a linked list.
 *
 * This function traverses a linked list starting from the given node
 * and returns a pointer to the last node in the list.
 *
 * @param lst A pointer to the first node of the linked list.
 *            If the list is empty (NULL), the behavior is undefined.
 *
 * @return A pointer to the last node in the linked list.
 */
t_blist	*get_last_node(t_blist *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
