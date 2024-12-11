/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:25:23 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/11 12:34:22 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_exit_status(int *status, int i)
{
    if (WIFEXITED(status[i]))
	{
		g_status = WEXITSTATUS(status[i]);
        // printf("Proceso %d: ", i);
		// printf("CÓDIGO SALIDA %d\n", g_status);
		// printf("INT STATUS en función %d\n", g_status);
	}
	else if (WIFSIGNALED(status[i]))
	{
		g_status = WTERMSIG(status[i]) + 128;
        // printf("Proceso %d: ", i);
		// printf("CÓDIGO SALIDA SEÑAL %d\n", g_status);
		// printf("INT STATUS en función %d\n", g_status);

	}
}