/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blstadd_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:24:26 by pablo             #+#    #+#             */
/*   Updated: 2025/05/09 12:20:24 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Adds a new element to the end of a doubly linked list.
 *
 * This function traverses the list to find the last element and appends the
 * new element to it. If the list is empty, the new element becomes the first
 * element. If either `lst` or `new` is NULL, the function does nothing.
 *
 * @param lst A pointer to the pointer of the first element of the list.
 *            If the list is empty, the new element will become the first
 *            element.
 * @param new A pointer to the new element to be added to the list.
 *            The new element's `previous` pointer will be updated to point to
 *            the last element of the list.
 */
void	blstadd_back(t_blist **lst, t_blist *new)
{
	t_blist	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
	new->previous = temp;

}
