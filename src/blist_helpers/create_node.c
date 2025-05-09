/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:25:41 by pablo             #+#    #+#             */
/*   Updated: 2025/05/09 21:00:49 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Creates a new node for a doubly linked list.
 *
 * This function allocates memory for a new node of type `t_blist` and
 * initializes its `value` field with the given integer `n`.
 *
 * @param n The integer value to be stored in the new node.
 *
 * @return A pointer to the newly created node, or NULL if memory allocation
 * fails.
 */
t_blist	*create_node(int n)
{
	t_blist	*node;

	node = malloc(sizeof(t_blist));
	if (!node)
		return (NULL);
	node->value = n;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}
