/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lstdelone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:01:27 by aolabarr          #+#    #+#             */
/*   Updated: 2024/04/27 13:49:04 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

void	ftps_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	free(lst);
	lst = NULL;
	return ;
}
