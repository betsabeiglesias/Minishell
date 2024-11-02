/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/11/02 16:47:23 by aolabarr         ###   ########.fr       */
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
	//printf("Prueba BBB\n");
	if(init_env(envp, mini))
		return (EXIT_FAILURE);
	//printf("Prueba CCC\n");
	while (envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		//printf("Prueba AAA: %s\n", mini->env[i]);
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
    	{
        	free_env(mini);
        	return (handle_error(ERR_ENVP), EXIT_FAILURE);
		}
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
