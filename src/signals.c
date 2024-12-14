/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:50:07 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/14 09:28:15 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setup_signal_handlers_shell(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_signal_father;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void    setup_signal_handlers_fork(void)
{
   struct sigaction    sa;

   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;
   sa.sa_handler = handle_signal_child;
   sigaction(SIGINT, &sa, NULL);
   sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signal_handlers_builtin(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_signal_child;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

//on_new_line: no mueve físicamente el cursor a una nueva línea, le dice a readline que prepare una nueva línea
//replace_line: borra la línea que el usuario estaba escribiendo por una cadena vacía
//redisplay: actualiza el prompt de la pantalla
//SIGINT: control + C
//SIGQUIT: control + contrabarra

void	handle_signal_father(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		printf(NEW_LINE);
		rl_on_new_line();
		rl_replace_line(EMPTY, 0);
		rl_redisplay();
		g_status = 130;
	}
}

int handle_eof_interactive(char *str)
{
	if (!str)
	{
		printf(EXIT);
		printf(NEW_LINE);
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
