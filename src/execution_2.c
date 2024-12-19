/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:46:02 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/19 16:46:43 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
