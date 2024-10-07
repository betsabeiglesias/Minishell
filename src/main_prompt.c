/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:56:42 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/05 17:19:31 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

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