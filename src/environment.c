/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/12/18 20:36:05 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env(t_mini *shell)
{
	int	i;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
	}
	free(shell->env);
	shell->env = NULL;
}

int	init_env(char **envp, t_mini *shell)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (!exist_oldpwd(envp))
	{
		i++;
		shell->oldpwd = false;
	}
	shell->env = ft_calloc((i + 1), sizeof(char *));
	if (shell->env == NULL)
	{
		handle_error(ERR_MALLOC);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	exist_oldpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD=", env[i], ft_strlen("OLDPWD=")))
			return (1);
		i++;
	}
	return (0);
}

int	get_my_env(char **envp, t_mini *shell)
{
	int	size;

	size = ft_matsize(envp);
	shell->env = NULL;
	if (init_env(envp, shell))
		return (handle_error(21), EXIT_FAILURE);
	if (ft_matdup(shell->env, envp, size))
		return (handle_error(ERR_MALLOC), size);
	if (shell->oldpwd == false)
	{
		shell->env[size] = ft_strdup("OLDPWD=");
		if (shell->env[size] == NULL)
		{
			free_env(shell);
			handle_error(ERR_ENVP);
			return (EXIT_FAILURE);
		}
		shell->env[size + 1] = NULL;
	}
	else
		shell->env[size] = NULL;
	return (EXIT_SUCCESS);
}

void	free_mini(t_mini *shell)
{
	int	i;

	if (shell)
	{
		if (shell->env)
		{
			i = 0;
			while (shell->env[i])
			{
				free(shell->env[i]);
				i++;
			}
			free(shell->env);
		}
		free(shell);
	}
}
