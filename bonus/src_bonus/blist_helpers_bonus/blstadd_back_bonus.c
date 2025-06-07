/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blstadd_back_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:24:26 by pablo             #+#    #+#             */
/*   Updated: 2025/06/07 12:34:19 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
