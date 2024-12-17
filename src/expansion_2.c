/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:31 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/17 18:40:37 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_varen(t_varenv *var, char *input, int i)
{
	var->start = i;
	var->len = len_var(input, i);
	var->value = ft_substr(input, i, var->len);
	if (!var->value)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	var->var_expanded = NULL;
	return (EXIT_SUCCESS);
}

int	only_dollar(char *input, int *i)
{
	if ((input)[*i + 1] == ' ' || (input)[*i + 1] == '\0')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	dollar_question(char **input, int *i)
{
	if ((*input)[*i + 1] == '?')
	{
		print_exitstatus(input, *i);
		*i = 0;
		return (1);
	}
	return (0);
}

int	print_exitstatus(char **input, int i)
{
	char	*prev;
	char	*post;
	char	*status;
	char	*temp;

	prev = ft_substr(*input, 0, i);
	if (!prev)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	post = ft_substr(*input, i + 2, ft_strlen(*input));
	if (!post)
	{
		free(prev);
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	}
	status = ft_itoa(g_status);
	temp = ft_strjoin_variadic(3, prev, status, post);
	free(prev);
	free(status);
	free(post);
	if (!temp)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	free(*input);
	*input = temp;
	return (EXIT_SUCCESS);
}
