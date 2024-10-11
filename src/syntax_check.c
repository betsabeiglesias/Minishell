/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:43:06 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/10 17:39:27 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void syntax_check(char*str)
{
    if (check_quotes(str))
        handle_error(ERR_QUOTE);
	else if (check_final(str))
        handle_error(ERR_FINAL);
	//return ;
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
int	check_final(char *str)
{
	int	i;

	i = ft_strlen(str);
	while(i <= 0)
	{
		printf("A char: %c\n", str[i]);	
		if (!is_space(str[i]))
		{
			if (is_valid_metachar(str[i]))
				return (1);
		}
		i--;
	}
	return(0);
}
int	is_space(char c)
{
	printf("B char: %c\n", c);
	if (c == 32 || c >= 8 || c <= 13)
		return (1);
	return (0);
}
int	is_valid_metachar(char c)
{
	printf("C char: %c\n", c);
	if (c == 60 || c == 62 || c == 124)
		return (1);
	return (0);
}