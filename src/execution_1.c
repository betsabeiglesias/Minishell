/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:38 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/23 19:03:53 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_execution(t_list *exe_lst, t_mini *shell)
{
	int		i;
    int     num_procs;

	num_procs = ft_lstsize(exe_lst);
	shell->pipes = create_pipes(num_procs);
    shell->pid = malloc(num_procs * sizeof(pid_t *));
	i = 0;
	while (i < num_procs)
	{
		shell->pid[i] = fork();
		if (shell->pid[i] == ERROR)
			return (handle_error(ERR_FORK), EXIT_FAILURE);
		else if (shell->pid[i] == 0)
		{
			exe_child((t_exec *)exe_lst->content, i, num_procs, shell);
		}
		i++;
        exe_lst = exe_lst->next;
	}
	close_pipes(shell, num_procs);
	wait_childs(shell, num_procs);
    free(shell->pid);
    shell->pid = NULL;
	return (EXIT_SUCCESS);
}

int exe_child(t_exec *node, int child, int num_procs, t_mini *shell)
{
    int fd_in;
    int fd_out;

	fd_in = 0;
	fd_out = 0;
	if (child != 0)
		dup2(shell->pipes[child - 1][RD_END], STDIN_FILENO);
	if (child != num_procs - 1)
		dup2(shell->pipes[child][WR_END], STDOUT_FILENO);
    if (node->filename_in != NULL)
    {
        fd_in = open(node->filename_in, O_RDONLY);
        if (fd_in == ERROR)
		    return (handle_error(ERR_OPEN), EXIT_FAILURE);
    }
    if (node->filename_out != NULL && node->out_append == 0)
        fd_out =  open(node->filename_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (node->filename_out != NULL && node->out_append == 1)
        fd_out = open(node->filename_out, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd_out == ERROR)
		return (handle_error(ERR_OPEN), EXIT_FAILURE);
    if (node->filename_in != NULL)
        dup2(fd_in, STDIN_FILENO);
	 if (node->filename_out != NULL)
        dup2(fd_out, STDOUT_FILENO);
    close_pipes(shell, num_procs); // entender esto bien!
	if (is_builtin(node->cmd_all[0]))
	{
		execute_builtin(node, shell);
	}
	else
	{
		execve(node->path, node->cmd_all, shell->env);
		handle_error(ERR_EXECVE);
	}
    return (EXIT_SUCCESS);
}

void	wait_childs(t_mini *shell, int num_procs)
{
	int	i;
	int	*status;

	(void)shell;
	status = malloc(sizeof(int) * num_procs);
	if (!status)
		handle_error(ERR_MALLOC);
	i = 0;
	while (i < num_procs)
	{
		wait(NULL);
		/*
		if (waitpid(shell->pid[i], &(status[i]), 0) == ERROR)
		{
			//free(status);
			handle_error(ERR_WAIT);
		}
		*/
		i++;
	}
	//free(status);
	return ;
}

int	**create_pipes(int num_procs)
{
	int		i;
	int		**pipes;

	i = 0;
	pipes = ft_malloc_mat_int(num_procs - 1, 2, sizeof(int));
	if (!pipes)
		return (handle_error(ERR_MALLOC), NULL);
	while (i < num_procs - 1)
	{
		if (pipe(pipes[i]) == ERROR)
			return (free(pipes), handle_error(ERR_PIPE), NULL);
		i++;
	}
	return (pipes);
}

void	close_pipes(t_mini *shell, int num_procs)
{
	int	i;

	i = 0;
	while (i < num_procs - 1)
	{
		close(shell->pipes[i][RD_END]);
		close(shell->pipes[i][WR_END]);
		i++;
	}
	return ;
}

