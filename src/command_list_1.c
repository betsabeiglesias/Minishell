/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/19 17:28:37 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_execution_list(t_list *tk_lst, t_mini *shell)
{
	t_list	*exe_lst;
	t_exec	*node;

	exe_lst = NULL;
	node = NULL;
	while (tk_lst != NULL)
	{
		node = init_variables(node, shell);
		handle_all_redir(tk_lst, &shell->is_redir, node);
		if (create_outfile(node, (char *)(tk_lst->content)))
			return (NULL);
		if (shell->is_redir == 0 && is_str_pipe((char *)(tk_lst->content)))
		{
			if (handle_pipe(tk_lst, node, shell, &exe_lst))
				return (NULL);
			node = NULL;
		}
		else if (shell->is_redir == 0)
			if (handle_commands(tk_lst, node))
				return (NULL);
		tk_lst = jump_to_next_token(shell->is_redir, tk_lst);
	}
	if (handle_last_save_node(&exe_lst, &node, shell))
		return (NULL);
	return (exe_lst);
}

t_exec	*init_variables(t_exec *node, t_mini *shell)
{
	shell->is_redir = 0;
	if (!node)
		node = init_cmd_node();
	return (node);
}

t_list	*jump_to_next_token(int is_redir, t_list *tk_lst)
{
	if (is_redir)
	{
		ft_free_v(tk_lst->content);
		tk_lst = tk_lst->next;
	}
	tk_lst = tk_lst->next;
	return (tk_lst);
}

int	handle_pipe(t_list *tk_lst, t_exec *node, t_mini *shell, t_list **exe_lst)
{
	ft_free_v(tk_lst->content);
	if (!is_builtin(node->cmd_all))
		handle_get_path(node, shell);
	if (save_exe_node(exe_lst, node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	handle_get_path(t_exec *node, t_mini *shell)
{
	if (!is_cmd_executable(node->cmd_all))
	{
		if (node->cmd_all != NULL)
			node->path = get_path(shell->all_paths, node->cmd_all[0]);
	}
	else
		node->path = ft_strdup(node->cmd_all[0]);
	return ;
}
