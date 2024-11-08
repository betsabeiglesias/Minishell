/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:31 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/06 13:45:13 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*do_expansion(t_mini *shell)
{
	int			i;
	t_varenv	var;
	char		**cmd_line;

	cmd_line = &shell->input;
	i = 0;
    while((*cmd_line)[i] != '\0')
	{
		if ((*cmd_line)[i] == '$' && !is_expansible(*cmd_line, i))
        {
            i++;
            init_varen(&var, *cmd_line, i);
            get_var_env(shell, &var);
         	insert_expanded_var(cmd_line, &var);
			// if (var.var_expanded != NULL)
			// 	i += ft_strlen(var.var_expanded);
			// else 
			// 	i += var.len;
			clean_varen(&var);
			i = 0;
		}
        i++;
	}
    return (*cmd_line);
}

void	init_varen(t_varenv *var, char *cmd_line, int i)
{
	var->start = i;
	var->len = len_var(cmd_line, i);
	var->value = ft_substr(cmd_line, i, var->len);
	var->var_expanded = NULL;
}

void	clean_varen(t_varenv *var)
{
	if (var->value)
	{
		free (var->value);
		var->value = NULL;
	}
	// if (var->var_expanded)
	// {
	// 	free (var->var_expanded);
	// 	var->var_expanded = NULL;
	// }
}


