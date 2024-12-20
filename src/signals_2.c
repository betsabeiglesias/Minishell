/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:43:27 by binary            #+#    #+#             */
/*   Updated: 2024/12/20 16:59:23 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signal_father(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd(NEW_LINE, STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line(EMPTY, 0);
		rl_redisplay();
		g_status = 130;
	}
}

int	handle_eof_interactive(char *str)
{
	if (!str)
	{
		ft_putstr_fd(EXIT, STDOUT_FILENO);
		ft_putstr_fd(NEW_LINE, STDOUT_FILENO);
		handle_error(EOF);
		exit (EXIT_SUCCESS);
	}
	if (*str == '\0')
	{
		free(str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	handle_signal_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd(NEW_LINE, STDOUT_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	handle_signal_builtin(int signum)
{
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		exit (131);
	}
}
