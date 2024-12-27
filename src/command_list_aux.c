/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:14:11 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/27 14:26:03 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_str_pipe(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) == 1 && *str == PIPE)
		return (1);
	return (0);
}

int	is_str_redir(char *str, char *redir)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, redir, ft_strlen(str)))
		return (1);
	return (0);
}

int	is_identical_str(char *str1, char *str2)
{
	if (!(ft_strncmp(str1, str2, ft_strlen(str2)))
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	else
		return (0);
}

char	*construct_path(char *cmd, char *path)
{
	char	*pathname;

	pathname = ft_strdup(EMPTY);
	pathname = ft_strjoin_freed(pathname, path);
	pathname = ft_strjoin_freed(pathname, SLASH);
	pathname = ft_strjoin_freed(pathname, cmd);
	return (pathname);
}
