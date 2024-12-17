/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:29:52 by binary            #+#    #+#             */
/*   Updated: 2024/12/17 18:40:54 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_varen(t_varenv *var)
{
	if (var->value)
	{
		free (var->value);
		var->value = NULL;
	}
}

int	len_var(char *input, int i)
{
	size_t	len;
	int		temp;

	temp = i;
	len = 0;
	// while (input[temp] && valid_char_env(input[temp]))
	while (input[temp] && input[temp] != ' ')
	{
		len++;
		temp++;
	}
	return (len);
}

int	valid_char_env(char c)
{
	if(ft_isalnum(c) || c == '_')
		return(1);
	return(0);
}