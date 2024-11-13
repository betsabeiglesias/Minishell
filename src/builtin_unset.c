/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:14 by binary            #+#    #+#             */
/*   Updated: 2024/11/13 12:52:36 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//var_name es el argumento de unset, pueden ser varios.
//hacer un check de los argumentos alnum y _

int builtin_unset(char *var_name, t_mini *shell)
{
    int     i;
    int     new_len;
    char    **new_env;

    i = 0;
    new_len;
    while(shell->env[i])
    {   
        if(ft_strncmp(var_name, shell->env[i], len(var_name)))
            continue ;
        i++;
        new_len++;
    }
    new_env = malloc(sizeof(char *) * (new_len + 1));
    if (!new_env)
		return(handle_error(ERR_MALLOC, EXIT_FAILURE));
	i = 0;
	new_len = 0;
    while(shell->env[i])
    {
        if(ft_strncmp(var_name, shell->env[i], len(var_name)))
        	continue ;
		new_env[new_len] = ft_strdup(shell->env[i]);
		if(!new_env[new_len])
		{
			ft_free_mat_str(new_env, new_len);
			return(handle_error(ERR_MALLOC), EXIT_FAILURE)
		}
		i++;
		new_len++; 
    }
	new_env[new_len] = '\0';
}
