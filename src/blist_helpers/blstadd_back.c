/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blstadd_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:24:26 by pablo             #+#    #+#             */
/*   Updated: 2025/05/27 20:10:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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
