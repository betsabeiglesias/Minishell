/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/10/28 14:32:11 by binary           ###   ########.fr       */
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

char	**init_env(char **envp, t_mini *mini)
{
	int		i;

	i = 0;
	mini->oldpwd = true;
	while (envp[i])
	{
		i++;
	}
	if (getenv("OLDPWD") == NULL)
	{
		i++;
		mini->oldpwd = false;
	}
	mini->env = ft_calloc((i + 1), sizeof(char *));
	if (mini->env == NULL)
		return (NULL); //handle_error
	else
		return (mini->env);
}

char	**get_my_env(char **envp, t_mini *mini)
{
	int	i;

	i = 0;
	if(!(mini->env = init_env(envp, mini)))
		return (NULL); //handle_error
	while (envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		if (mini->env[i] == NULL)
		{
			free_env(mini); //handle_error if mini libera
			return (NULL);
		}
		i++;
	}
	if (mini->oldpwd == false)
	{
		
		mini->env[i] = ft_strdup("OLDPWD=");
		if (mini->env[i] == NULL)
    	{
        	free_env(mini);
        	return (NULL);
		}
		i++;
		mini->env[i] = NULL;
	}
	else
	mini->env[i] = NULL;
	return (mini->env);
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


// int main(int argc, char **argv, char **envp)
// {
//     // (void) argc;
//     // (void) argv;
// 	t_mini mini;
// 	//char *s;
	
// 	if (argc != 2)
// 	{
// 		printf("incorrect arguments");
// 		return(1);
// 	}
// 	mini.env = get_my_env(envp, &mini);
// 	// s = expand_varenv(argv[1], &mini);
// 	// printf("%s\n", s);

// 	printf("%s\n", expand_varenv(argv[1], &mini));
	


//     // int i = 0;
//     // mini.env = get_my_env(envp, &mini);
//     // while(mini.env[i])
//     // {
// 	// 	printf("esto es el env: %s\n",mini.env[i]);
// 	// 	i++;
//     // }
// 	// str = getenv("PATH");
// 	// printf("\n\n%s\n\n", str);
// 	// free_env(&mini);
// 	return (0);
// }
