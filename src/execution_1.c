/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/16 16:32:04 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

int	init_execution(t_list *exe_lst, t_mini *shell)
{
	int		i;
    int     num_procs;
	// int		num_builts;

	num_procs = ft_lstsize(exe_lst);
	// num_builts = builtin_count(exe_lst);
	shell->num_pipes = num_procs - 1;
	shell->pipes = create_pipes(num_procs);
	if (!shell->pipes)
		return(EXIT_FAILURE);
	i = 0;
	if (num_procs == 1 && is_builtin(((t_exec *)exe_lst->content)->cmd_all))
		handle_exec_onlybuilt((t_exec *)exe_lst->content, shell);
	else
	{
		shell->pid = malloc(num_procs * sizeof(pid_t));
		if (!shell->pid)
			return(handle_error(ERR_MALLOC), EXIT_FAILURE);	
		setup_signal_handlers_fork();
		while (i < num_procs)
		{
			shell->pid[i] = fork();
			if (shell->pid[i] == ERROR)
				return (handle_error(ERR_FORK), EXIT_FAILURE);
			else if (shell->pid[i] == 0)
			{
				if (exe_child((t_exec *)exe_lst->content, i, num_procs, shell))
					return (EXIT_FAILURE);
			}
			i++;
			exe_lst = exe_lst->next;
		}
	}
	close_pipes(shell, num_procs);
	if (shell->pid != NULL)
		wait_childs(shell, num_procs);
	setup_signal_handlers_shell();
	return (EXIT_SUCCESS);
}

int exe_child(t_exec *node, int child, int num_procs, t_mini *shell)
{
	if (is_builtin(node->cmd_all))
		setup_signal_handlers_builtin();
	else
		setup_signal_handlers_fork();	/*se puede borrar */
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
		else if(execve(node->path, node->cmd_all, shell->env) == ERROR)
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
		if (is_builtin(((t_exec *)exe_lst->content)->cmd_all))
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
    if (node->filename_in != NULL && ft_strncmp(node->filename_in, HERE_DOC, ft_strlen(HERE_DOC)))
    {
        fd_in = open(node->filename_in, O_RDONLY);
        if (fd_in == ERROR)
			return (handle_error(ERR_OPEN), EXIT_FAILURE);
    }
	else if(node->filename_in != NULL && !ft_strncmp(node->filename_in, HERE_DOC, ft_strlen(HERE_DOC)))
	{
		fd_in = create_here_doc_file(node->heredoc_content);
		if (fd_in == ERROR)
			return(EXIT_FAILURE);
	}
	if (do_redirections_continue(node, fd_in, fd_out))
		return(EXIT_FAILURE);
	close_pipes(shell, num_procs);
	return (EXIT_SUCCESS);
}

int do_redirections_continue(t_exec *node, int fd_in, int fd_out)
{
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
	return (EXIT_SUCCESS);
} 


int create_here_doc_file(char *heredoc_content)
{
	int fd_in;

	fd_in = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_in == ERROR)
		return (handle_error(ERR_OPEN), ERROR);
	ft_putstr_fd(heredoc_content, fd_in);
	close(fd_in);
	fd_in = open(HERE_DOC, O_CREAT | O_RDONLY, 0644);
	return (fd_in);
}

















/* FUNCION ORIGINAL
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
    if (node->filename_in != NULL && ft_strncmp(node->filename_in, HERE_DOC, ft_strlen(HERE_DOC)))
    {
        fd_in = open(node->filename_in, O_RDONLY);
        if (fd_in == ERROR)
			return (handle_error(ERR_OPEN), EXIT_FAILURE);
    }
	else if(node->filename_in != NULL && !ft_strncmp(node->filename_in, HERE_DOC, ft_strlen(HERE_DOC)))
	{
		fd_in = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_in == ERROR)
		{
			return (handle_error(ERR_OPEN), EXIT_FAILURE);
		}
		ft_putstr_fd(node->heredoc_content, fd_in);
		close(fd_in);
		fd_in = open(HERE_DOC, O_CREAT | O_RDONLY, 0644);
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
	close_pipes(shell, num_procs);
	return (EXIT_SUCCESS);
}
*/

