/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:09:42 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 13:01:16 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    init_shell(t_mini *shell)
{
   shell->env = NULL;
   shell->input = NULL;
   shell->oldpwd = true;
   get_all_paths(shell);
   shell->paths = NULL;
   return ;
}

int	get_all_paths(t_mini *shell)
{
	size_t	i;
	int		get;
	char	**paths;

	if (!shell->env)
		return (EXIT_FAILURE);
	i = 0;
	get = 0;
	while (i < ft_matsize(shell->env) && get == 0)
	{
		if (!ft_strncmp(shell->env[i], PATH, ft_strlen(PATH)))
		{
			paths = ft_split(shell->env[i] + ft_strlen(PATH), DOTS);
			get = 1;
		}
		i++;
	}
	shell->all_paths = paths;
	return (EXIT_SUCCESS);
}