/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:45:48 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/27 14:24:45 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_here_doc_file(char *hdoc_content)
{
	int	fd_in;

	fd_in = open(HERE_DOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_in == ERROR)
		return (handle_error(ERR_OPEN), ERROR);
	ft_putstr_fd(hdoc_content, fd_in);
	close(fd_in);
	fd_in = open(HERE_DOC, O_CREAT | O_RDONLY, 0644);
	return (fd_in);
}

void	get_exit_status(int *status, int i)
{
	if (WIFEXITED(status[i]))
	{
		g_status = WEXITSTATUS(status[i]);
	}
	else if (WIFSIGNALED(status[i]))
	{
		g_status = WTERMSIG(status[i]) + 128;
	}
}
