/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:31:21 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/12 13:04:21 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signal_interactive (int signum)
{
	(void)signum;
	printf("entra en handle\n");
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line(); //no mueve físicamente el cursor a una nueva línea, le dice a readline que prepare una nueva línea
		rl_replace_line("", 0); //borra la línea que el usuario estaba escribiendo por una cadena vacía
		rl_redisplay(); //actualiza el prompt de la pantalla
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line(); 
		//rl_replace_line("recibe ctrl+\\ \n", 0); 
		rl_redisplay(); 
	}
}

void setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_signal_interactive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void handle_eof_interactive (char *str)
{
	if (!str)
	{
		printf("exit\n"); 
		exit(0);
	}
}

char *prompt(void)
{
	char *str;
	
	setup_signal_handlers();

	while(1)
	{
		//printf("estoy en prompt\n");
    	str = readline("minishell> ");
		handle_eof_interactive(str);
		if (str && *str)
			add_history(str);
		if (!ft_strncmp(str, "exit", ft_strlen(str)))
		{
			free(str);
			exit(0);
		}
		free(str);
	}    
    return (str);
}
