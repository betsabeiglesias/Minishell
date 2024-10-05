/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:31:21 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/05 13:30:05 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char *prompt(void)
{
	char *str;

    str = readline("minishell> ");
	add_history(str);
        
    return (str);
    
}

int main()
{
	char *line;

	while(1)
	{	
		line = prompt( );
		free(line);
		if (line == NULL) // Detecta EOF (Ctrl+D)
    		break;

	}
	
	return(0);
}