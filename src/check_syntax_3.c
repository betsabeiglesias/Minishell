/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:52:31 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:04 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_metachar_consecutive(char *str)
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
		if (s_quote == false && d_quote == false
			&& is_redir_metachar(str[i]) && is_space(str[i + 1]))
		{
			if (do_check_consecutive(str, i))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	do_check_consecutive(char *str, int i)
{
	i++;
	while (str[i] == SPA_C)
		i++;
	if (str[i] == PIPE || is_redir_metachar(str[i]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
