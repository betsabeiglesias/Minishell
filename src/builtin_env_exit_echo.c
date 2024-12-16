/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exit_echo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/16 16:43:40 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	builtin_env(t_mini *shell, int fd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{		
		ft_putstr_fd(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_exec *node, t_mini *shell)
{
	int	arg;
	(void)shell;
	arg = ft_matsize(node->cmd_all) - 1;
	if (arg == 0)
		g_status = 0;
	else if (ft_str_hasalpha(node->cmd_all[1]))
	{
		ft_putstr_fd("exit: " , STDOUT_FILENO);
		ft_putstr_fd(node->cmd_all[1], STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		g_status = 2;
	}
	else if (arg > 1)
	{
		ft_putstr_fd("exit: too many arguments\n" , STDOUT_FILENO);
		g_status= 1;
		exit(g_status);
	}
	else
		g_status = ft_atoi_exit(node->cmd_all[1]);
	print_exit();
	// free_shell(shell);
	exit(g_status);
}

int	builtin_echo(t_exec *node, int fd)
{
	int		i;
	bool	flag;
	int	   	arg;	

	i = 1;
	flag = false;
	arg = ft_matsize(node->cmd_all) - 1;
	if(arg == 0)
		return (EXIT_SUCCESS);
	if (!ft_strncmp(node->cmd_all[i], "-n", ft_strlen(node->cmd_all[1])))
	{
		i++;
		flag = true;
	}
	while (node->cmd_all[i])
	{
		ft_putstr_fd(node->cmd_all[i], fd);
		i++;
		ft_putchar_fd(' ', fd);
	}
	if (flag == false)
		ft_putchar_fd('\n', fd);
	return (EXIT_SUCCESS);
}
