/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:43:08 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/23 15:27:09 by aolabarr         ###   ########.fr       */
/*                                                                            */
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
void	free_shell(t_mini *shell)
{	
	//printf("Prueba A: %p\t%p\t%s\n", shell->env, shell->env[0], shell->env[0]);
	//printf("Prueba B: %ld\n", ft_matsize(shell->env));
	if (shell->env)
		ft_free_mat_str(shell->env, ft_matsize(shell->env));
	if (shell->input)
		ft_free(shell->input);
	shell->env = NULL;
	shell->input = NULL;
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
void lst_clear_exec(t_list *lst) // meter int num_procs)
{
	t_exec *node;
	
	while (lst)
	{
		node = (t_exec *)lst->content;
		ft_free_mat_str(node->cmd_all, ft_matsize(node->cmd_all));
		ft_free(node->path);
		ft_free(node->filename_in);
		ft_free(node->filename_out);
		ft_free(node->heredoc_content);
		ft_free_exec(node);
		node = NULL;
		//ft_free_mat_int(node->pipes, num_procs);
		lst = lst->next;
	}
	return ;
}

void	ft_free_exec(t_exec *str)
{
	if (str)
		free(str);
	return ;
}
