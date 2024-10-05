/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:17:46 by aolabarr          #+#    #+#             */
/*   Updated: 2024/04/27 13:33:58 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

void	ftps_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		ftps_lstadd_front(lst, new);
		return ;
	}
	node = *lst;
	while ((node -> next) != NULL)
		node = node -> next;
	node -> next = new;
	return ;
}
