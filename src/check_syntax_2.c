/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:34:49 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:04 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_metachar_separate(char *str)
{
	size_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (i < ft_strlen(str))
	{
		new_quote_status(&s_quote, &d_quote, i, str);
		if (s_quote == false && d_quote == false && is_valid_metachar(str[i]))
		{
			if (do_check(str, i))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	do_check(char *str, int i)
{
	if (check_pipe_separate(str, i))
		return (EXIT_FAILURE);
	if (check_redir_separate(str, i, '>'))
		return (EXIT_FAILURE);
	if (check_redir_separate(str, i, '<'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_pipe_separate(char *str, int i)
{
	if (str[i] == PIPE)
	{
		if (str[i - 1] == SPA_C && str[i + 1] == SPA_C)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_redir_separate(char *str, int i, char c)
{
	if (str[i] == c && i == 0)
	{
		if (str[i + 1] == SPA_C || (str[i + 1] == c && str[i + 2] == SPA_C))
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	else if (str[i] == c && i == 1)
	{
		if (str[i - 1] == SPA_C && str[i + 1] == SPA_C)
			return (EXIT_SUCCESS);
		else if (str[i - 1] == SPA_C && str[i + 1] == c && str[i + 2] == SPA_C)
			return (EXIT_SUCCESS);
		else if (str[i - 1] == c && str[i + 1] == SPA_C)
			return (EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	else if (str[i] == c)
	{
		if (do_redir_check(str, i, c))
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	do_redir_check(char *str, int i, char c)
{
	if (str[i - 1] == SPA_C && str[i + 1] == SPA_C)
		return (EXIT_SUCCESS);
	else if (str[i - 1] == SPA_C && str[i + 1] == c && str[i + 2] == SPA_C)
		return (EXIT_SUCCESS);
	else if (str[i - 2] == SPA_C && str[i - 1] == c && str[i + 1] == SPA_C)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
