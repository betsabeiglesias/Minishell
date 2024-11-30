/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:56:38 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/30 13:05:37 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_execution(t_list *exe_lst, t_mini *shell)
{
	int		i;
    int     num_procs;
	int		num_builts;

	num_procs = ft_lstsize(exe_lst);
	num_builts = builtin_count(exe_lst);
	shell->num_pipes = num_procs - 1;
	shell->pipes = create_pipes(num_procs);
	if (!shell->pipes)
		return(EXIT_FAILURE);
    shell->pid = malloc((num_procs - num_builts) * sizeof(pid_t *));
	if (!shell->pid)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);	
	i = 0;
	while (i < num_procs)
	{
		
		{
			shell->pid[i] = fork();
			if (shell->pid[i] == ERROR)
				return (handle_error(ERR_FORK), EXIT_FAILURE);
			else if (shell->pid[i] == 0)
			{
				if (exe_child((t_exec *)exe_lst->content, i, num_procs, shell))
					return (EXIT_FAILURE);
			}
		}
		i++;
        exe_lst = exe_lst->next;
	}
	close_pipes(shell, num_procs);
	wait_childs(shell, num_procs);
    ft_free_v((void *)shell->pid);
    shell->pid = NULL;
	return (EXIT_SUCCESS);
}

int exe_child(t_exec *node, int child, int num_procs, t_mini *shell)
{
	if (do_redirections(node, child, num_procs, shell))
		return (EXIT_FAILURE);
	if (is_builtin((node->cmd_all[0])))
	{
		execute_builtin(node, shell);
		exit(EXIT_SUCCESS);
	}
	else
		execve(node->path, node->cmd_all, shell->env);
	handle_error(ERR_EXECVE);
    return (EXIT_FAILURE);
}

int	wait_childs(t_mini *shell, int num_procs)
{
	int	i;
	int	*status;

	(void)shell;
	status = malloc(sizeof(int) * num_procs);
	if (!status)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	i = 0;
	while (i < num_procs)
	{
		//wait(NULL);
		if (waitpid(shell->pid[i], &(status[i]), 0) == ERROR)
		{
			free(status);
			handle_error(ERR_WAIT);
			return (EXIT_FAILURE);
		}
		i++;
	}
	free(status);
	return (EXIT_SUCCESS);
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
			return (ft_free_v((void *)pipes), handle_error(ERR_PIPE), NULL);
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

int	builtin_count(t_list *exe_lst)
{
	int count;

	count = 0;
	while(exe_lst != NULL)
	{
		if (is_builtin(((t_exec *)exe_lst->content)->cmd_all[0]))
			count ++;
		exe_lst = exe_lst->next;
	}
	return (count);
}
int do_redirections(t_exec *node, int child, int num_procs, t_mini *shell)
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
        fd_out =  open(node->filename_out, O_CREAT | O_RDWR | O_TRUNC, 644);
    else if (node->filename_out != NULL && node->out_append == 1)
        fd_out = open(node->filename_out, O_CREAT | O_RDWR | O_APPEND, 644);
    if (fd_out == ERROR)
		return (handle_error(ERR_OPEN), EXIT_FAILURE);
    if (node->filename_in != NULL)
        dup2(fd_in, STDIN_FILENO);
	 if (node->filename_out != NULL)
        dup2(fd_out, STDOUT_FILENO);
	close_pipes(shell, num_procs);
	return (EXIT_SUCCESS);
}

