/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:31:21 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/05 16:15:13 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_signal_prompt(int num)
{
	rl_on_new_line();
}

char *prompt(void)
{
	char *str;

    str = readline("minishell> ");
	add_history(str);
	        
    return (str);
}
