/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:31 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/11 12:35:34 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*do_expansion(t_mini *shell)
{
	int			i;
	t_varenv	var;
	char		**input;

	input = &shell->input;
	i = 0;
    while((*input)[i] != '\0')
	{
		if ((*input)[i] == '$' && is_expansible(*input, i))
        {
			if((*input)[i+1] == ' ' || (*input)[i+1] =='\0')
			{	
				i++;
				continue;
			}
			else if((*input)[i+1] == '?')
			{
				print_exitstatus(input, i);
				i = 0;
			}
			else
			{
				i++;
				if(init_varen(&var, *input, i))
					return(NULL);
				if(get_var_env(shell, &var) == 0)
				{
					if(insert_expanded_var(input, &var))
						return (NULL);
				// if (var.var_expanded != NULL)
				// 	i += ft_strlen(var.var_expanded);
				// else 
				// 	i += var.len;
				}
				clean_varen(&var);
				i = 0;
			}
		}
        i++;
	}
    return (*input);
}


int	init_varen(t_varenv *var, char *input, int i)
{
	var->start = i;
	var->len = len_var(input, i);
	var->value = ft_substr(input, i, var->len);
	if(!var->value)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	var->var_expanded = NULL;
	return (EXIT_SUCCESS);
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

int print_exitstatus(char **input, int i)
{
	char	*prev;
	char	*post;
	char	*status;
	char	*temp;

	prev = ft_substr(*input, 0, i);
	if (!prev)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	post = ft_substr(*input, i+2, ft_strlen(*input));
	if (!post)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	status = ft_itoa(g_status);
	// printf("INT STATUS %d\n", g_status);
	// printf("ITOA %s\n", status);
	temp = ft_strjoin_variadic(3, prev, status, post);
	if (!temp)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	free(*input);
	*input = temp;
	return (EXIT_SUCCESS);
}

