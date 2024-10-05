/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:31:21 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/05 17:57:00 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signal_prompt(int signum)
{
	(void)signum;
	printf("entra en handle\n");
	rl_on_new_line();
	rl_replace_line("nuevaminishell> ", 0);
	rl_redisplay();
}

char *prompt(void)
{
	char *str;
	struct sigaction sa;
	
	sa.sa_handler = handle_signal_prompt;
	sigemptyset(&sa.sa_mask); 

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	printf("estoy en prompt\n");
    str = readline("minishell> ");
	add_history(str);
		        
    return (str);
}
