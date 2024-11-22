/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:53:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/22 10:05:06 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_env(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

void	builtin_exit(char *cmd_all)
{
	if (!ft_strncmp(cmd_all, "exit", ft_strlen(cmd_all)))
		exit(EXIT_SUCCESS);
}

void	builtin_echo(char **cmd_all)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (!ft_strncmp(cmd_all[i], "-n", ft_strlen(cmd_all[1])))
	{
		i++;
		flag = true;
	}
	while (cmd_all[i])
	{
		ft_putstr_fd(cmd_all[i], STDOUT_FILENO);
		i++;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
