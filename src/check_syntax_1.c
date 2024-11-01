/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:06 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/01 11:16:07 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int syntax_check(char *str)
{
    if (is_str_space(str))
        return (EXIT_FAILURE);
	else if (check_quotes(str))
        return (handle_error(ERR_QUOTE), EXIT_FAILURE);
	else if (check_extrems(str))
        return (handle_error(ERR_EXTREM), EXIT_FAILURE);
	else if (check_metachar_separate(str))
        return (handle_error(ERR_ALONE), EXIT_FAILURE);
	return (EXIT_SUCCESS) ;
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
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int	check_extrems(char *str)
{
	int	i;

	i = 0;
	while(is_space(str[i]))
		i++;
	if (str[i] == '|')
		return (EXIT_FAILURE);
	i = ft_strlen(str) - 1;
	while(is_space(str[i]))
		i--;
	if (is_valid_metachar(str[i]))
		return (EXIT_FAILURE);
	return(EXIT_SUCCESS);
}



