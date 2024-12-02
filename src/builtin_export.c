/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:56:51 by binary            #+#    #+#             */
/*   Updated: 2024/12/02 13:25:12 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_export(t_exec *node, t_mini *shell)
{
	int	args;

	args = 1;
	if (node->cmd_all[args])
	{
		/* MODIFICAR A CMD */		
		if (export_args(node->cmd_all[1], shell))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	export_no_args(shell);
	return (EXIT_SUCCESS);
}

int	export_args(char *str, t_mini *shell)
{
	size_t	len;
	size_t	i;
	char	**new_env;

	if(!check_namevar(str))
		return(handle_error(ERR_EXPORT), EXIT_FAILURE);
	len = ft_matsize(shell->env);
	i = 0;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (i < len)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if (!new_env[i])
			return (handle_error(ERR_MALLOC), EXIT_FAILURE);
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	new_env[i + 1] = NULL;
	ft_free_mat_str(shell->env, len);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	check_namevar(char *str)
{
	int	i;
	int last;
	
	i = 0;
	last = ft_strlen(str) - 1;
	while (is_space(str[i]))
		i++;
	if((str[i] >= 65 && str[i] <= 90) || str[i] == '_')
		i++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else if ((str[i] >= 65 && str[i] <= 90) || str[i] == '_')
			i++;
		else
			return (0);
	}
	if (str[last] != '=')
		return(0);	
	return (1);
}

void	export_no_args(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		print_export(shell->env[i]);
		ft_putstr_fd("\n", STDIN_FILENO);
		i++;
	}
}

void	print_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], STDIN_FILENO);
		if (str[i] == '=')
			ft_putchar_fd('\"', STDIN_FILENO);
		i++;
	}
	ft_putchar_fd('\"', STDIN_FILENO);
}
