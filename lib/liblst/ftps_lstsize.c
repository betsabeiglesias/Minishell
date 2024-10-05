/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lstsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:48:21 by aolabarr          #+#    #+#             */
/*   Updated: 2024/05/05 17:59:45 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

int	ftps_lstsize(t_list *lst)
{
	int		count;
	t_list	*node;

	count = 0;
	node = lst;
	if (lst == NULL)
		return (count);
	while (node != NULL)
	{
		count++;
		node = node -> next;
	}
	return (count);
}
