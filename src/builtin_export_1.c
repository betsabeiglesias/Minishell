/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:56:51 by binary            #+#    #+#             */
/*   Updated: 2024/12/26 15:18:53 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_export(t_exec *node, t_mini *shell, int fd)
{
	int	args;

	args = 1;
	if (!node->cmd_all[args])
		export_no_args(shell, fd);
	while (node->cmd_all[args])
	{
		if (check_namevar(node->cmd_all[args]))
		{
			printf("export: %s: not a valid identifier\n", node->cmd_all[args]);
			args++;
			continue ;
		}
		if (export_args(node->cmd_all[args], shell))
			return (EXIT_FAILURE);
		args++;
	}
	return (EXIT_SUCCESS);
}

int	change_var_value(char *str, t_mini *shell)
{
	int	i;
	int	len_name;

	i = 0;
	len_name = len_var_name(str);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, len_name) && \
			(shell->env[i][len_name] == '=' || shell->env[i][len_name] == '\0'))
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(str);
			if (!shell->env[i])
				return (handle_error(ERR_MALLOC), EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	export_args(char *str, t_mini *shell)
{
	if (!change_var_value(str, shell))
		return (EXIT_SUCCESS);
	if (!add_newvar(str, shell))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	add_newvar(char *str, t_mini *shell)
{
	size_t	len;
	char	**new_env;

	len = ft_matsize(shell->env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	if (ft_matdup(new_env, shell->env, len))
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	new_env[len] = ft_strdup(str);
	if (!new_env[len])
	{
		while (len > 0)
			free(new_env[--len]);
		free(new_env);
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	}
	new_env[len + 1] = NULL;
	ft_free_mat_str(shell->env, len);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	check_namevar(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (!ft_isalpha(str[i]) || str[i] == '_')
		return (1);
	i++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (1);
		i++;
	}
	return (0);
}
