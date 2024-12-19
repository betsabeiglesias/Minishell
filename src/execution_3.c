/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:45:48 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/19 17:02:44 by aolabarr         ###   ########.fr       */
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
