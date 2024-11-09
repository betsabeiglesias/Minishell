/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:18:03 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 13:37:01 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_str_pipe(char *str)
{
	if(!str)
		return (0);
	if (ft_strlen(str) == 1 && *str == PIPE)
		return (1);
	return (0);
}
int	is_str_redir(char *str, char *redir)
{
	if(!str)
		return (0);
	if (!ft_strncmp(str, redir, ft_strlen(str)))
		return (1);
	return (0);
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
		pathname = ft_strdup("");
		pathname = ft_strjoin_freed(pathname, all_paths[i]);
		pathname = ft_strjoin_freed(pathname, SLASH);
		pathname = ft_strjoin_freed(pathname, cmd);
		if (access(pathname, X_OK) == ACCESS)
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (pathname);
}



