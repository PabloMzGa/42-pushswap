/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:25:41 by pablo             #+#    #+#             */
/*   Updated: 2025/06/07 12:34:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
