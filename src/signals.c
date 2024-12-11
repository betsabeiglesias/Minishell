/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:50:07 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/11 13:11:21 by beiglesi         ###   ########.fr       */
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

void    setup_signal_handlers_notinteract(void)
{
   struct sigaction    sa;

   sa.sa_handler = handle_signal_notinteractive;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART;
   sigaction(SIGINT, &sa, NULL);
   //sigaction(SIGQUIT, &sa, NULL);
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
		g_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
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
void	handle_signal_notinteractive(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);	
    //    rl_on_new_line();
    //    rl_replace_line(EMPTY, 0);
    //    rl_redisplay();
	}
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}
