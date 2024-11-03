/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/03 14:12:23 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_command_list(t_list *tk_lst)
{
	t_list	*cmd_lst;
	t_list	node;

	cmd_lst = NULL;
	while(tk_lst != NULL)
	{
		init_cmd_node(&node);
		tk_lst = tk_lst->next;
	}
	return (cmd_lst);
}

void init_cmd_node(t_list *node)
{
	node->env = NULL;
	node->cmd = NULL;
	node->cmd_all = NULL;
	node->path = NULL;
	node->fd_in = 0;
	node->fd_out = 0;
	return ;
}
