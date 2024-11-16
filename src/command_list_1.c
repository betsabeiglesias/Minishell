/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/16 18:55:18 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_command_list(t_list *tk_lst, t_mini *shell)
{
	t_list	*cmd_lst;
	t_exec	*node;
	int		is_redir;

	(void)shell; // guardar los nodos en la struct shell

	cmd_lst = NULL;
	node = NULL;
	while(tk_lst != NULL)
	{
		//printf("\n\n\n\n\n\nVAMOS...\n");
		is_redir = 0;
		if (!node)
			node = init_cmd_node();
		if (is_str_redir((char *)(tk_lst->content), REDIR_IN_S))
			is_redir = handle_redir(tk_lst, node, REDIR_IN_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_IN_D))
			is_redir = handle_redir(tk_lst, node, REDIR_IN_D);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_S))
			is_redir = handle_redir(tk_lst, node, REDIR_OUT_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_D))
			is_redir = handle_redir(tk_lst, node, REDIR_OUT_D);
		/*
		else if (is_str_pipe((char *)(tk_lst->content)))
		{
		handle_pipe(cmd_lst, &node, shell);
			//liberar node;
		}
		*/
		else
		{
			if (handle_commands(tk_lst, node))
				return(NULL);
		}
		if (is_redir)
			tk_lst = tk_lst->next;
		tk_lst = tk_lst->next;
	}
	//PRINTS
	printf("\nINFO de EXEC\n");
	printf("filename IN: %s\n", node->filename_in);
	printf("filename OUT: %s\n", node->filename_out);
	printf("here doc: %s\n", node->heredoc_content);
	print_cmd_all(node->cmd_all);

	return (cmd_lst);
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
		node->filename_in = HERE_DOC;
		read_stdin(node, delimiter);
	}
	else if (!ft_strncmp(redir, REDIR_OUT_S, ft_strlen(redir)))
		node->filename_out = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_OUT_D, ft_strlen(redir)))
		node->filename_out = (char *)tk_lst->next->content;
	return (EXIT_SUCCESS);
}

int	read_stdin(t_exec *node, char *delimiter)
{
	char	*buffer;

	node->heredoc_content = ft_strdup(EMPTY);
	buffer = ft_strdup(EMPTY);
	if (!buffer || !node->heredoc_content)
		return (ft_free(buffer), ft_free(delimiter), handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (buffer)
	{
		if (buffer)
			ft_free(buffer);
		buffer = get_next_line(STDIN_FILENO);
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


