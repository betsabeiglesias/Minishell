/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 13:35:41 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_command_list(t_list *tk_lst, t_mini *shell)
{
	t_list	*cmd_lst;
	t_exec	*node;
	int		is_redir;

	cmd_lst = NULL;
	while(tk_lst != NULL)
	{
		is_redir = 0;
		node = init_cmd_node();
		if (is_str_redir((char *)(tk_lst->content), REDIR_IN_S))
			is_redir = handle_redir_in(tk_lst, node, shell, REDIR_IN_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_IN_D))
			is_redir = handle_redir_in(tk_lst, node, shell, REDIR_IN_D);
		/*
		if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_S))
			is_redir = handle_redir_out(tk_lst, &node, shell, REDIR_OUT_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_D))
			is_redir = handle_redir_out(tk_lst, &node, shell, REDIR_OUT_D);
		else if (is_str_pipe((char *)(tk_lst->content)))
			handle_pipe(cmd_lst, &node, shell);
		
		else
			handle_cmd(tk_lst, &node);
		*/
		if (is_redir)
			tk_lst = tk_lst->next;
		tk_lst = tk_lst->next;
	}
	return (cmd_lst);
}

t_exec *init_cmd_node(void)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	node->env = NULL;
	node->cmd = NULL;
	node->cmd_all = NULL;
	node->path = NULL;
	node->fd_in = 0;
	node->fd_out = 0;
	return (node);
}

int	handle_redir_in(t_list *tk_lst, t_exec *node, t_mini *shell, char *redir)
{
	char *filename;
	
	filename = (char *)tk_lst->next->content;
	(void)shell;
	(void)node;
	(void)redir;
	return (0);
}
