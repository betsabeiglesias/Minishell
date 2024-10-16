/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/16 22:10:30 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

char	*expand_varenv(char *str, t_mini *mini)
{
	char	*var;
	size_t	len;
	
	// if (!str || str[0] != '$')
	// 	return(NULL);
	len = ft_strlen(str) - 1;
	// if(len == 0)
	//	return(NULL);
	var = malloc (sizeof(char) * (len + 2));
	if(!var || !str)
		return(NULL);
	ft_strlcpy(var, str + 1, len + 1);
	var[len] = '=';
	var[len + 1] = '\0';
	while(*mini->env != NULL)
	{
		if (!ft_strncmp(*mini->env, var, len + 1))
		{
			free(var);
			return(*mini->env + (len + 1));
		}
		mini->env++;
	}
	free(var);
	//handle_error(ERR_ENVP);
	return (str);
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