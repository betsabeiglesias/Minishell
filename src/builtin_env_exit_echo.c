/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:53:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/06 12:31:38 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_env(t_mini *shell, int fd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{		
		ft_putstr_fd(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	builtin_exit(t_exec *node)
{
	int	arg;
	int nb;
	arg = ft_matsize(node->cmd_all) - 1;
	if(arg == 0)
		only_exit();
	if(ft_str_hasalpha(node->cmd_all[1]))
	{
		ft_putstr_fd("exit: " , STDOUT_FILENO);
		ft_putstr_fd(node->cmd_all[1], STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		exit(2);
		//valor de salida para $?
	}
	if(arg > 1)
	{
		ft_putstr_fd("exit: too many arguments\n" , STDOUT_FILENO);
		exit(2);
		//valor de salida para $?
	}
	else
	{
		nb = ft_atoi_exit(node->cmd_all[1]);
		exit(nb);
	}
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
