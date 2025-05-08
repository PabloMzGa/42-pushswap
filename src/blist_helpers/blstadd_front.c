/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blstadd_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:12:11 by pabmart2          #+#    #+#             */
/*   Updated: 2025/05/08 11:03:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * @brief Adds a new element to the front of a doubly linked list.
 *
 * This function inserts a new element at the beginning of a doubly linked list.
 * It updates the `next` pointer of the new element to point to the current head
 * of the list and updates the `previous` pointer of the current head to point
 * back to the new element. Finally, it updates the head of the list to the new
 * element.
 *
 * @param lst A pointer to the pointer of the head of the doubly linked list.
 *            If the list is empty, *lst should be NULL.
 * @param new A pointer to the new element to be added to the list. The `new`
 *            element must not be NULL and should be properly initialized.
 */
void	blstadd_front(t_blist **lst, t_blist *new)
{
	new->next = *lst;
	(*lst)->previous = new;
	*lst = new;
}
