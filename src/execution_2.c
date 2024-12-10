/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:25:23 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/10 09:46:34 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_exit_status(int *status, int i, t_mini *shell)
{
    if (WIFEXITED(status[i]))
	{
		shell->exit_status = WEXITSTATUS(status[i]);
        // printf("Proceso %d: ", i);
		// printf("CÓDIGO SALIDA %d\n", shell->exit_status);
		// printf("INT STATUS en función %d\n", shell->exit_status);
	}
	else if (WIFSIGNALED(status[i]))
	{
		shell->exit_status = WTERMSIG(status[i]) + 128;
        // printf("Proceso %d: ", i);
		// printf("CÓDIGO SALIDA SEÑAL %d\n", shell->exit_status);
		// printf("INT STATUS en función %d\n", shell->exit_status);

	}
}