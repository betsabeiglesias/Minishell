/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:06 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/05 17:20:44 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_quotes(char *str)
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
        return (false);
    else
        return (true);
    return (0);
}
