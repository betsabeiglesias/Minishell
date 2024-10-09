/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/10/09 11:19:17 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_mini{
    char        **env;
}               t_mini;

void free_env(t_mini *mini)
{
	int	i;

	i = 0;
	while(mini->env[i])
	{
		free(mini->env[i]);
		i++;
	}
	free(mini->env);
}

char    **init_env(char **envp)
{
    int     i;
    char    **mini_env;
    i = 0;
    while(envp[i])
        i++;
    mini_env = malloc(sizeof(char *) * i + 1);
    if (mini_env == NULL)
        return (NULL);
    return(mini_env);  
}

char **get_env(char **envp, t_mini *mini)
{
	int	i;

	i = 0;
	mini->env = init_env(envp);
	if(mini->env == NULL)
		return (NULL);
	while (envp[i])
	{
		mini->env[i] = ft_strdup(envp[i]);
		if(mini->env[i] == NULL)
			free_env(mini);
		i++;
	}
	mini->env[i] = '\0';
	return(mini->env);
}


int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
	t_mini mini;
	char *str;

    int i = 0;
    mini.env = get_env(envp, &mini);
    while(mini.env[i])
    {
        printf("esto es el env: %s\n",mini.env[i]);
        i++;
    }
	str = getenv("PATH");
	printf("\n\n%s\n\n", str);

	free_env(&mini);
    return(0);

}