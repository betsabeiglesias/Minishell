/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:26 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/20 16:49:29 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_error(int error_type)
{
	if (error_type == ERR_QUOTE)
		ft_putendl_fd(ERR_MSG_QUOTE, STDOUT_FILENO);
	if (error_type == ERR_EXTREM)
		ft_putendl_fd(ERR_MSG_EXTREM, STDOUT_FILENO);
	if (error_type == ERR_ALONE)
		ft_putendl_fd(ERR_MSG_ALONE, STDOUT_FILENO);
	if (error_type == ERR_CONSECUTIVE)
		ft_putendl_fd(ERR_MSG_CONSEC, STDOUT_FILENO);
	if (error_type == ERR_ENVP)
		ft_putendl_fd(ERR_MSG_ENVP, STDOUT_FILENO);
	if (error_type == ERR_ATTR)
		ft_putendl_fd(ERR_MSG_ATTR, STDOUT_FILENO);
	if (error_type == ERR_MALLOC)
		perror(ERR_MSG_MALLOC);
	handle_error_continue(error_type);
	return (EXIT_FAILURE);
}

void	handle_error_continue(int error_type)
{
	if (error_type == ERR_ACCESS)
		perror(ERR_MSG_ACCESS);
	if (error_type == ERR_OPEN)
		perror(ERR_MSG_OPEN);
	if (error_type == ERR_BUILT)
		ft_putendl_fd(ERR_MSG_BUILT, STDOUT_FILENO);
	if (error_type == ERR_EXPORT)
		ft_putendl_fd(ERR_MSG_EXPORT, STDOUT_FILENO);
	if (error_type == ERR_EXECVE)
		perror(ERR_MSG_EXECVE);
	if (error_type == ERR_CHDIR)
		perror(ERR_MSG_CHDIR);
	if (error_type == ERR_HERE)
		perror(ERR_MSG_HERE);
	if (error_type == ERR_GETWD)
		perror(ERR_MSG_GETWD);
	if (error_type == ERR_EOF)
		ft_putendl_fd(ERR_MSG_EOF, STDOUT_FILENO);
	return ;
}
