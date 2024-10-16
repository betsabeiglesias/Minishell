/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/16 13:08:46 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

char	*expand_varenv(char *str, t_mini *mini)
{
	char	*var;
	size_t	len;
	bool	exist;
	// if (!str || str[0] != '$')
	// 	return(NULL);
	exist = false;
	len = ft_strlen(str) - 1;
	var = malloc (sizeof(char) * (len + 2));
	if(!var || !str)
		return(NULL);
	ft_strlcpy(var, str + 1, len + 1);
	var[len] = '=';
	var[len + 1] = '\0';
	while(*mini->env)
	{
		if (!ft_strncmp(*mini->env, var, len + 1))
		{
			free(var);
			return(*mini->env + (len + 1));
		}
		mini->env++;
	}
	if (exist == false)
	{
		free(var);
		handle_error(ERR_ENVP);
	}
	return (NULL);
}

// int main(int ac, char **av, char **env)
// {
// 	if(ac != 2)
// 	{
// 		printf("incorrect arguments\n");
// 		return(1);
// 	}
// 	printf("%s\n", expand_varenv(av[1],env));
// 	return(0);

// }