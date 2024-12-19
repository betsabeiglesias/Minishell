/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:24:19 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/19 17:35:30 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_all_redir(t_list *tk_lst, int *is_redir, t_exec *node)
{
	if (is_str_redir((char *)(tk_lst->content), REDIR_IN_S))
		*is_redir = handle_redir(tk_lst, node, REDIR_IN_S);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_IN_D))
		*is_redir = handle_redir(tk_lst, node, REDIR_IN_D);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_S))
		*is_redir = handle_redir(tk_lst, node, REDIR_OUT_S);
	else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_D))
		*is_redir = handle_redir(tk_lst, node, REDIR_OUT_D);
	return ;
}

int	handle_redir(t_list *tk_lst, t_exec *node, char *redir)
{
	char	*delimiter;

	if (!ft_strncmp(redir, REDIR_IN_S, ft_strlen(redir)))
		node->filename_in = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_IN_D, ft_strlen(redir)))
	{
		delimiter = (char *)tk_lst->next->content;
		delimiter = ft_strjoin_freed(delimiter, NEW_LINE);
		node->filename_in = ft_strdup(HERE_DOC);
		read_stdin(node, delimiter);
	}
	else if (!ft_strncmp(redir, REDIR_OUT_S, ft_strlen(redir)))
		node->filename_out = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_OUT_D, ft_strlen(redir)))
	{
		node->filename_out = (char *)tk_lst->next->content;
		node->out_append = 1;
	}
	return (1);
}

int	create_outfile(t_exec *node, char *redir)
{
	int	fd;

	if (!ft_strncmp(redir, REDIR_OUT_S, ft_strlen(redir))
		|| !ft_strncmp(redir, REDIR_OUT_D, ft_strlen(redir)))
	{
		fd = open(node->filename_out, O_CREAT, 0644);
		if (fd == ERROR)
			return (handle_error(ERR_OPEN), EXIT_FAILURE);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	read_stdin(t_exec *node, char *delimiter)
{
	char	*buffer;

	node->heredoc_content = ft_strdup(EMPTY);
	buffer = ft_strdup(EMPTY);
	if (!buffer || !node->heredoc_content)
		return (ft_free(buffer), ft_free(delimiter), handle_error(ERR_MALLOC),
			EXIT_FAILURE);
	while (buffer)
	{
		if (buffer)
			ft_free(buffer);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			return (ft_free(delimiter), ft_free(buffer), handle_error(ERR_EOF),
				EXIT_FAILURE);
		if (is_identical_str(buffer, delimiter))
		{
			ft_free(delimiter);
			ft_free(buffer);
			break ;
		}
		if (buffer)
			node->heredoc_content = ft_strjoin_freed(node->heredoc_content, buffer);
	}
	return (EXIT_SUCCESS);
}

int is_cmd_executable(char **cmd_all)
{
	if (cmd_all == NULL)
		return (0);
	if (ft_strlen(*cmd_all) < 3)
		return (0);
	if ((*cmd_all)[0] == POINT && (*cmd_all)[1] == SLASH_CHAR)
		return (1);
	return (0);
}
