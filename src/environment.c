/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/11/02 17:56:35 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void	free_env(t_mini *mini)
{
	int	i;

	if (mini->env)
	{
		i = 0;
		while (mini->env[i])
		{
			free(mini->env[i]);
			i++;
		}
	}
	free(mini->env);
	mini->env = NULL;
}

int	init_env(char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (getenv("OLDPWD") == NULL)
	{
		i++;
		mini->oldpwd = false;
	}
	mini->env = ft_calloc((i + 1), sizeof(char *));
	if (mini->env == NULL)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	return(EXIT_SUCCESS) ;
}

int	get_my_env(char **envp, t_mini *mini)
{
	int	i;

	i = 0;
	if(init_env(envp, mini))
		return (EXIT_FAILURE);
	while (envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		if (mini->env[i] == NULL)
		{
			free_env(mini);
			return (handle_error(ERR_ENVP), EXIT_FAILURE);
		}
		i++;
	}
	if (mini->oldpwd == false)
	{
		mini->env[i] = ft_strdup("OLDPWD=");
		if (mini->env[i] == NULL)
        	return (free_env(mini), handle_error(ERR_ENVP), EXIT_FAILURE);
		i++;
		mini->env[i] = NULL;
	}
	else
		mini->env[i] = NULL;
	return (EXIT_SUCCESS);
}

void free_mini(t_mini *mini)
{
	int	i;

	if (mini)
	{
		if(mini->env)
		{
			i = 0;
			while(mini->env[i])
			{
				free(mini->env[i]);
				i++;
			}
			free(mini->env);
		}
		free(mini);
	}
}
