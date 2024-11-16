/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:18:03 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/16 20:46:36 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int handle_commands(t_list *tk_lst, t_exec *node)
{
	if (!node->cmd_all)
	{
		node->cmd_all = malloc(sizeof(char *));
		if (!node->cmd_all)
			return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	}
	node->cmd_all = add_token_to_cmd(node->cmd_all, (char *)tk_lst->content);
	if (!node->cmd_all)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char **add_token_to_cmd(char **cmd_all, char *str)
{
	char	**dst;
	size_t	size;
	size_t	i;

	dst = NULL;
	size = ft_matsize(cmd_all);
	dst = malloc(sizeof(char *) * (size + 2));
	if (!dst)
	{
		ft_free_mat_str(cmd_all, ft_matsize(cmd_all));
		return(handle_error(ERR_MALLOC), NULL);
	}
	i = 0;
	while (i < size)
	{
		dst[i] = cmd_all[i];
		i++;
	}
	dst[i] = str;
	dst[i + 1] = NULL;
	return (dst);
}

char	*get_path(char **all_paths, char *cmd)
{
	char	*pathname;
	size_t	i;

	if (!all_paths)
		return (NULL);
	i = 0;
	while (i < ft_matsize(all_paths))
	{
		pathname = ft_strdup(EMPTY);
		pathname = ft_strjoin_freed(pathname, all_paths[i]);
		pathname = ft_strjoin_freed(pathname, SLASH);
		pathname = ft_strjoin_freed(pathname, cmd);
		if (!pathname)
			return (handle_error(ERR_MALLOC), NULL);
		if (access(pathname, X_OK) == ACCESS)
			break ;
		ft_free(pathname);
		pathname = NULL;
		i++;
	}
	if (!pathname)
		return (handle_error(ERR_ACCESS), NULL);
	return (pathname);
}

