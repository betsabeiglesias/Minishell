/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:58:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 19:13:11 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*create_command_list(t_list *tk_lst, t_mini *shell)
{
	t_list	*cmd_lst;
	t_exec	*node;
	int		is_redir;

	cmd_lst = NULL;
	while(tk_lst != NULL)
	{
		is_redir = 0;
		if (!node)
			node = init_cmd_node();
		if (is_str_redir((char *)(tk_lst->content), REDIR_IN_S))
			is_redir = handle_redir_in(tk_lst, node, shell, REDIR_IN_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_IN_D))
			is_redir = handle_redir_in(tk_lst, node, shell, REDIR_IN_D);

		/*
		if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_S))
			is_redir = handle_redir_out(tk_lst, &node, shell, REDIR_OUT_S);
		else if (is_str_redir((char *)(tk_lst->content), REDIR_OUT_D))
			is_redir = handle_redir_out(tk_lst, &node, shell, REDIR_OUT_D);
		else if (is_str_pipe((char *)(tk_lst->content)))
			handle_pipe(cmd_lst, &node, shell);
		
		else
			handle_cmd(tk_lst, &node);
		*/
		printf("here doc: %s\n", node->heredoc_content);
		if (is_redir)
			tk_lst = tk_lst->next;
		tk_lst = tk_lst->next;
	}
	return (cmd_lst);
}

t_exec *init_cmd_node(void)
{
	t_exec *node;
	
	node = malloc(sizeof(t_exec));
	if (!node)
		return (handle_error(ERR_MALLOC), NULL);
	node->env = NULL;
	node->cmd = NULL;
	node->cmd_all = NULL;
	node->path = NULL;
	node->filename_in = NULL;
	node->filename_out = NULL;
	node->heredoc_content = ft_strdup("");
	if (!node->heredoc_content)
		return (handle_error(ERR_MALLOC), NULL); //liberar node
	//node->here_doc = 0;
	return (node);
}

int	handle_redir_in(t_list *tk_lst, t_exec *node, t_mini *shell, char *redir)
{
	char	*delimiter;

	if (!ft_strncmp(redir, REDIR_IN_S, ft_strlen(redir)))
		node->filename_in = (char *)tk_lst->next->content;
	else if (!ft_strncmp(redir, REDIR_IN_D, ft_strlen(redir)))
	{
		delimiter = (char *)tk_lst->next->content;
		node->filename_in = HERE_DOC;
		read_stdin(node, delimiter);
	}
	(void)shell;
	return (EXIT_SUCCESS);
}


int	read_stdin(t_exec *node, char *delimiter)
{
	char	*buffer;

	delimiter = ft_strjoin(delimiter, "\n");
	buffer = ft_strdup("");
	if (!buffer || !delimiter)
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
			//write(fd, buffer, ft_strlen(buffer));
	}
	return (EXIT_SUCCESS);
}

int	is_identical_str(char *str1, char *str2)
{
	if (!(ft_strncmp(str1, str2, ft_strlen(str2)))
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	else
		return (0);
}
