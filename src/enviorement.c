/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviorement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:08:15 by binary            #+#    #+#             */
/*   Updated: 2024/10/08 10:31:11 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_mini{
    char        **env;
}               t_mini;


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