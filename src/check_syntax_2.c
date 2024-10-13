/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:34:49 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/13 13:54:41 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_metachar_separate(char *str)
{
	size_t	i;
	t_quote	quote;

	i = 0;
	quote.sing = false;
    quote.doub = false;
	while (i < ft_strlen(str))
    {
        if (str[i] == '\'' && quote.sing == false && quote.doub == false)
            quote.sing = true;
        else if (str[i] == '\'' && quote.sing == true && quote.doub == false)
            quote.sing = false;
        else if (str[i] == '"' && quote.sing == false && quote.doub == false)
            quote.doub = true;
        else if (str[i] == '"' && quote.sing == false && quote.doub == true)
            quote.doub = false;
		if (quote.sing == false && quote.doub == false && is_valid_metachar(str[i]))
		{
			if (do_check(str, i))
				return (1);
		}
		i++;
    }
	return (0);
}

int do_check(char *str, int i)
{
	if (check_pipe_separate(str, i))
		return (1);
	if (check_redir_separate(str, i, '>'))
		return (1);
	if (check_redir_separate(str, i, '<'))
		return (1);
	return (0);
}

int	check_pipe_separate(char *str, int i)
{
	if (str[i] == '|')
	{
		if (str[i - 1] == ' ' && str[i + 1] == ' ')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	check_redir_separate(char *str, int i, char c)
{
	if (str[i] == c && i == 0)
	{
		if (str[i + 1] == ' ' || (str[i + 1] == c && str[i + 2] == ' '))
			return (0);
		else
			return (1);
	}
	else if (str[i] == c && i == 1)
	{
		if (str[i - 1] == ' ' && str[i + 1] == ' ')
			return (0);
		else if (str[i - 1] == ' ' && str[i + 1] == c && str[i + 2] == ' ')
			return (0);
		else
			return (1);
	}
	else if (str[i] == c)
	{
		if (do_redir_check(str, i, c))
			return (1);
		else
			return (0);
	}
	return (0);
}
int	do_redir_check(char *str,int i, char c)
{
	if (str[i - 1] == ' ' && str[i + 1] == ' ')
		return (0);
	else if (str[i - 1] == ' ' && str[i + 1] == c && str[i + 2] == ' ')
		return (0);
	else if (str[i - 2] == ' ' && str[i - 1] == c && str[i + 1] == ' ')
		return (0);
	return (1);
}
