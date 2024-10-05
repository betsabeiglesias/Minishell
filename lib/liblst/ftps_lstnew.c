/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftps_lstnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:54:46 by aolabarr          #+#    #+#             */
/*   Updated: 2024/05/03 17:04:01 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

t_list	*ftps_lstnew(int content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = content;
	node -> idx = 0;
	node -> cost.total = 0;
	node -> cost.ra = 0;
	node -> cost.rb = 0;
	node -> cost.rra = 0;
	node -> cost.rrb = 0;
	node -> next = NULL;
	return (node);
}
