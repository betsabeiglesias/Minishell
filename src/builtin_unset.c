/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:14 by binary            #+#    #+#             */
/*   Updated: 2024/11/15 17:31:56 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//var_name es el argumento de unset, pueden ser varios.
//hacer un check de los argumentos alnum y _

int builtin_unset(char *var_name, t_mini *shell)
{
    int     i;
    int     new_len;
	int		j;
    char    **new_env;

	i = 0;
	j = 0;
    new_len = new_reduced_size_env(var_name, shell);
	new_env = malloc(sizeof(char *) * (new_len + 1));
    if (!new_env)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
    while(shell->env[i])
    {
        if(ft_strncmp(var_name, shell->env[i], ft_strlen(var_name)) != 0)
      	{
			new_env[j] = ft_strdup(shell->env[i]);
			if(!new_env[j])
			{
				ft_free_mat_str(new_env, new_len);
				return(handle_error(ERR_MALLOC), EXIT_FAILURE);
			}
		}
		i++;
		j++;
	}
	new_env[j] = '\0';
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	new_reduced_size_env(char *var_name, t_mini *shell)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while(shell->env[i])
    {   
        if(!ft_strncmp(var_name, shell->env[i], ft_strlen(var_name)))
			i++;
        else
        {
			i++;
        	size++;
    	}
	}
	return(size);
}
