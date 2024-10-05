/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lstclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:20:09 by aolabarr          #+#    #+#             */
/*   Updated: 2024/06/02 12:10:17 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

void	ftps_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*follow;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst != NULL)
	{
		follow = (*lst)->next;
		ftps_lstdelone(*lst, del);
		*lst = follow;
	}
	lst = NULL;
	return ;
}
