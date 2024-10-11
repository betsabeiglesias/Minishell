/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:06 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/11 20:31:48 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int syntax_check(char*str)
{
	if (check_quotes(str))
        return(handle_error(ERR_QUOTE), 1);
	else if (check_extrems(str))
        return(handle_error(ERR_EXTREM), 1);
	else if (check_metachar_separate(str))
        return(handle_error(ERR_ALONE), 1);
	return (0) ;
}

int	check_quotes(char *str)
{
    bool	s_quote;
    bool	d_quote;
    size_t  i;

    s_quote = false;
    d_quote = false;
    i = 0;
    while (i < ft_strlen(str))
    {
        if (str[i] == '\'' && s_quote == false && d_quote == false)
            s_quote = true;
        else if (str[i] == '\'' && s_quote == true && d_quote == false)
            s_quote = false;
        else if (str[i] == '"' && s_quote == false && d_quote == false)
            d_quote = true;
        else if (str[i] == '"' && s_quote == false && d_quote == true)
            d_quote = false;
        i++;
    }
    if (s_quote == true || d_quote == true)
        return (1);
    return (0);
}
int	is_str_space(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!is_space(str[i]))
			return (0);
	}
	return (1);
}

int	check_extrems(char *str)
{
	int	i;

	i = 0;
	while(is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (1);
	i = ft_strlen(str) - 1;
	while(is_space(str[i]))
		i--;
	if (is_valid_metachar(str[i]))
		return (1);
	return(0);
}

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
        if (str[i] == '\'' && s_quote == false && d_quote == false)
            s_quote = true;
        else if (str[i] == '\'' && s_quote == true && d_quote == false)
            s_quote = false;
        else if (str[i] == '"' && s_quote == false && d_quote == false)
            d_quote = true;
        else if (str[i] == '"' && s_quote == false && d_quote == true)
            d_quote = false;
		if (s_quote == false && d_quote == false && is_valid_metachar(str[i]))
		{
			if (i == 0)
			{
				if (str[i + 1] != ' ')
					return (1);
			}
			else
			{
				if (str[i - 1] != ' ' || str[i + 1] != ' ')
					return (1);
			}
		}
		i++;
    }
	return (0);
}

int	is_space(char c)
{
	if (c == 32 || (c >= 8 && c <= 13))
		return (1);
	return (0);
}
int	is_valid_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}