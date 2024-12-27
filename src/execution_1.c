/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:07:14 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/20 17:16:52 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_execution(t_list *exe_lst, t_mini *shell)
{
	int	num_procs;

	num_procs = ft_lstsize(exe_lst);
	shell->num_pipes = num_procs - 1;
	shell->pipes = create_pipes(num_procs);
	if (!shell->pipes)
		return (EXIT_FAILURE);
	if (num_procs == 1 && is_builtin(((t_exec *)exe_lst->content)->cmd_all))
		handle_exec_onlybuilt((t_exec *)exe_lst->content, shell);
	else
	{
		shell->pid = malloc(num_procs * sizeof(pid_t));
		if (!shell->pid)
			return (handle_error(ERR_MALLOC), EXIT_FAILURE);
		setup_signal_handlers_fork();
		if (create_process(exe_lst, num_procs, shell))
			return (EXIT_FAILURE);
	}
	close_pipes(shell, num_procs);
	if (shell->pid != NULL)
		wait_childs(shell, num_procs);
	setup_signal_handlers_shell();
	return (EXIT_SUCCESS);
}

int	create_process(t_list *exe_lst, int num_procs, t_mini *shell)
{
	int	i;

	i = 0;
	while (i < num_procs)
	{
		shell->pid[i] = fork();
		if (shell->pid[i] == ERROR)
			return (handle_error(ERR_FORK), EXIT_FAILURE);
		else if (shell->pid[i] == 0)
		{
			if (exe_child((t_exec *)exe_lst->content, i, num_procs, shell))
				exit(EXIT_FAILURE);
		}
		i++;
		exe_lst = exe_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	exe_child(t_exec *node, int child, int num_procs, t_mini *shell)
{
	if (is_builtin(node->cmd_all))
		setup_signal_handlers_builtin();
	else
		setup_signal_handlers_fork();
	if (do_redirections(node, child, num_procs, shell))
		return (EXIT_FAILURE);
	if (is_builtin((node->cmd_all)))
	{
		execute_builtin(node, shell);
		exit(g_status);
	}
	else
	{
		if (node->path == NULL && node->cmd_all != NULL)
		{
			handle_error(ERR_ACCESS);
			exit(EXIT_FAILURE);
		}
		else if (node->path == NULL && node->cmd_all == NULL)
			exit(EXIT_FAILURE);
		else if (execve(node->path, node->cmd_all, shell->env) == ERROR)
			handle_error(ERR_EXECVE);
		exit(EXIT_FAILURE);
	}
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
		if (waitpid(shell->pid[i], &(status[i]), 0) == ERROR)
		{
			free(status);
			handle_error(ERR_WAIT);
			return (EXIT_FAILURE);
		}
		get_exit_status(status, i);
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
