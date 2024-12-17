/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/17 19:51:20 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../inc/minishell.h"

void	lst_clear_token_content(t_list *lst)
{
	int	i;
	int	size;

	size = ft_lstsize(lst);
	i = 0;
	while (i < size)
	{
		ft_free(lst->content);
		lst = lst->next;
		i++;
	}
	return ;
}

void	free_shell(t_mini *shell)
{
	if (shell->env)
		ft_free_mat_str(shell->env, ft_matsize(shell->env));
	if (shell->all_paths)
		ft_free_mat_str(shell->all_paths, ft_matsize(shell->all_paths));
	// //if (shell->paths)
	// //	ft_free_mat_str(shell->paths, ft_matsize(shell->paths));
	// if (shell->input)
	// 	ft_free(shell->input);
	// //if (shell->pid)
	// //	ft_free_v((void *)shell->pid);
	// //if (shell->pipes)
	// //	ft_free_mat_int(shell->pipes, shell->num_pipes);
	// shell->env = NULL;
	// shell->input = NULL;
	// shell->all_paths = NULL;
	// //shell->paths = NULL;
	// //shell->pid = NULL;
	// //shell->pipes = NULL;
	// free(shell);
	// shell = NULL;
	return ;
}

void	ft_free_mat_int(int **mat, int size)
{
	int	i;

	if (!mat)
		return ;
	i = 0;
	while (i < size)
		free(mat[i++]);
	free(mat);
	mat = NULL;
	return ;
}
void lst_clear_exec(t_list *lst)
{
	//t_exec *node;
	
	while (lst)
	{
		free_node_exec((t_exec *)lst->content);
		lst->content = NULL;
		lst = lst->next;
	}
	return ;
}
void free_node_exec(t_exec *node)
{
	if (!node)
		return ;
	ft_free_mat_str(node->cmd_all, ft_matsize(node->cmd_all));
	//printf("info dir: %p %s\n", node->path, node->path);
	ft_free(node->path);
	ft_free(node->filename_in);
	ft_free(node->filename_out);
	ft_free(node->heredoc_content);
	ft_free_v((void *)node);
	node = NULL;
	return ;
}

void	ft_free_v(void *str)
{
	if (str)
		free(str);
	return ;
}

/*
void handle_free(t_mini shell, int error)
{
	(void)shell;

	if (error == ERR_ENVP)
	{
		//liberar todo shell
	}	
	else if (error == EOF)
	{
		//liberar todo shell
	}
	return ;
}
*/
