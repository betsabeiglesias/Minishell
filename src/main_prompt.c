/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:56:42 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/16 11:19:17 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	char **line;

	line = prompt( );
	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])))
		builtin_cd(line);
	free(line);
	    	
	return(0);
}