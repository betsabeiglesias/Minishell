/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:53:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/30 16:55:35 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_env(t_mini *shell, int fd)
{
	int	i;

	i = 0;
	//print_env(shell);
	//printf("Dirección de shell->env EN BUILTIN: %p\n\n\n", shell->env);
	// printf("FD de ENV %i, dir %p\n", fd, &fd);
	while (shell->env[i])
	{
		//printf("env[%d]: %s (Dirección: %p)\n", i, shell->env[i], (void *)shell->env[i]);
		
		ft_putstr_fd(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	builtin_exit(t_exec *node)
{
	if (!ft_strncmp(node->cmd_all[0], "exit", ft_strlen(node->cmd_all[0])))
		exit(EXIT_SUCCESS);
}

void	builtin_echo(t_exec *node)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (!ft_strncmp(node->cmd_all[i], "-n", ft_strlen(node->cmd_all[1])))
	{
		i++;
		flag = true;
	}
	while (node->cmd_all[i])
	{
		ft_putstr_fd(node->cmd_all[i], STDOUT_FILENO);
		i++;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
