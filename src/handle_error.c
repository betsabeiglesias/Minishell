/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:26 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/05 19:50:19 by aolabarr         ###   ########.fr       */
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
		ft_putendl_fd(ERR_MSG_CONSECUTIVE, STDOUT_FILENO);
	if (error_type == ERR_ENVP)
		ft_putendl_fd(ERR_MSG_ENVP, STDOUT_FILENO);
	if (error_type == ERR_ATTR)
		ft_putendl_fd(ERR_MSG_ATTR, STDOUT_FILENO);
	if (error_type == ERR_MALLOC)
		ft_putendl_fd(ERR_MSG_MALLOC, STDOUT_FILENO);
	if (error_type == ERR_ACCESS)
		perror(ERR_MSG_ACCESS);
	if (error_type == ERR_OPEN)
		ft_putendl_fd(ERR_MSG_OPEN, STDOUT_FILENO);
	if (error_type == ERR_EXECVE)
		perror(ERR_MSG_EXECVE);
	return (EXIT_FAILURE);
}