/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:38 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/21 21:07:00 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_execution(t_list *exe_lst, t_mini *shell)
{
	int		i;
    int     num_childs;

	i = 0;
    num_childs = ft_lstsize(exe_lst);
    shell->pid = malloc( num_childs * sizeof(pid_t *));
	while (i < num_childs)
	{
		shell->pid[i] = fork();
		if (shell->pid[i] == ERROR)
			return (handle_error(ERR_FORK), EXIT_FAILURE);
		else if (shell->pid[i] == 0)
			exe_child((t_exec *)exe_lst->content, i, num_childs, shell->env);
		i++;
        exe_lst = exe_lst->next;
	}
	//close_pipes(data);
	wait_childs(shell, num_childs);
    //free(shell->pid);
    shell->pid = NULL;
	return (EXIT_SUCCESS);
}

int exe_child(t_exec *node, int child, int num_childs, char **env)
{
    int fd_in;
    int fd_out;


    node->pipes = create_pipes(num_childs);

	if (child != 0)
		dup2(node->pipes[child - 1][RD_END], STDIN_FILENO);
	if (child != num_childs - 1)
		dup2(node->pipes[child][WR_END], STDOUT_FILENO);
    if (node->filename_in != NULL)
    {
        fd_in = open(node->filename_in, O_RDONLY);
        if (fd_in == ERROR)
		    return (handle_error(ERR_OPEN), EXIT_FAILURE);
    }
    if (node->filename_out != NULL || node->out_append == 0)
        fd_out =  open(node->filename_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (node->filename_out != NULL || node->out_append == 1)
        fd_out = open(node->filename_out, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd_out == ERROR)
		return (handle_error(ERR_OPEN), EXIT_FAILURE);
    if (node->filename_in != NULL)
        dup2(node->pipes[child - 1][RD_END], STDIN_FILENO);
	
    close_pipes(node, num_childs);
	execve(node->path, node->cmd_all, env);
	handle_error(ERR_EXECVE);
    return (EXIT_SUCCESS);
}

void	wait_childs(t_mini *shell, int num_childs)
{
	int	i;
	int	*status;

	status = malloc(sizeof(int) * num_childs);
	if (!status)
		handle_error(ERR_MALLOC);
	i = 0;
	while (i < num_childs)
	{
		if (waitpid(shell->pid[i], &(status[i]), 0) == ERROR)
		{
			free(status);
			handle_error(ERR_WAIT);
		}
		i++;
	}
	free(status);
	return ;
}

int	**create_pipes(int num_childs)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = ft_malloc_mat_int(num_childs - 1, 2, sizeof(int));
	if (!pipes)
		return (handle_error(ERR_MALLOC), NULL);
	while (i < num_childs - 1)
	{
		if (pipe(pipes[i]) == ERROR)
			return (free(pipes), handle_error(ERR_MALLOC), NULL);
		i++;
	}
	return (pipes);
}

void	close_pipes(t_exec *node, int num_childs)
{
	int	i;

	i = 0;
	while (i < num_childs - 1)
	{
		close(node->pipes[i][RD_END]);
		close(node->pipes[i][WR_END]);
		i++;
	}
	return ;
}

