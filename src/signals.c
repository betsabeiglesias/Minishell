/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:50:07 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 17:43:36 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_signal_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
//on_new_line: no mueve físicamente el cursor a una nueva línea, le dice a readline que prepare una nueva línea
//replace_line: borra la línea que el usuario estaba escribiendo por una cadena vacía
//redisplay: actualiza el prompt de la pantalla
//SIGINT: control + C
//SIGQUIT: control + contrabarra

void	handle_signal_interactive(int signum)
{
	(void)signum;
	if (signum == SIGINT)
	{
		printf(NEW_LINE);
		rl_on_new_line();
		rl_replace_line(EMPTY, 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_eof_interactive(char *str)
{
	if (!str)
	{
		printf(EXIT);
		printf(NEW_LINE);
		handle_error(EOF);
		exit(EXIT_SUCCESS);
	}
}
