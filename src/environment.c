/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/11/25 12:23:39 by binary           ###   ########.fr       */
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
	if(!exist_oldpwd(envp))
	{
		i++;
		shell->oldpwd = false;
	}
	shell->env = ft_calloc((i + 1), sizeof(char *));
	if (shell->env == NULL)
	{
		handle_error(ERR_MALLOC);
		return(EXIT_FAILURE);
	}
	//liberar env en el punto donde falla
	return(EXIT_SUCCESS) ;
}
int	exist_oldpwd(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{	
		if(!ft_strncmp("OLDPWD=", env[i], ft_strlen("OLDPWD=")))
			return(1);
		i++;
	}
	return (0);

}


int	get_my_env(char **envp, t_mini *shell)
{
	int	i;

	i = 0;
	if(init_env(envp, shell))
	{
		printf("Error en init_env\n");
		return (EXIT_FAILURE);
	}
	while (envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (shell->env[i] == NULL)
		{
			free_env(shell);
			return (handle_error(ERR_ENVP), EXIT_FAILURE);
		}
		i++;
	}
	if (shell->oldpwd == false)
	{
		shell->env[i] = ft_strdup("OLDPWD=");
		if (shell->env[i] == NULL)
		{
        	free_env(shell);
			handle_error(ERR_ENVP);
			return(EXIT_FAILURE);
		}
		i++;
		shell->env[i] = NULL;
	}
	else
	{
		shell->env[i] = NULL;
	}
	return (EXIT_SUCCESS);
}

void free_mini(t_mini *shell)
{
	int	i;

	if (shell)
	{
		if(shell->env)
		{
			i = 0;
			while(shell->env[i])
			{
				free(shell->env[i]);
				i++;
			}
			free(shell->env);
		}
		free(shell);
	}
}
