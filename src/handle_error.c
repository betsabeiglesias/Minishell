/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:26 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/16 13:08:43 by beiglesi         ###   ########.fr       */
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
	if (error_type == ERR_ENVP)
		ft_putendl_fd(ERR_MSG_ENVP, STDOUT_FILENO);
	return (1);
}