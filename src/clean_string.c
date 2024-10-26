/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:06:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/26 12:08:47 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *clean_string(char *str)
{
	char	*dst;
	int		i;
	t_quote	quote;
	int		old_len;

	dst =ft_strdup("");
	i = 0;
	while(str[i])
	{
		while(str[i] == ' ')
			i++;
		if (str[i] == SINGLE_QUOTE)
		{
			old_len = ft_strlen(dst);
			dst = add_literal_str(dst, str[i + 1], SINGLE_QUOTE);
			i = i + ft_strlen(dst) - old_len + 1;
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			old_len = ft_strlen(dst);
			dst = add_literal_str(dst, str[i + 1], DOUBLE_QUOTE);
		}
		else
		{
			old_len = ft_strlen(dst);
			dst = add_literal_str(dst, str[i + 1], SPACE);
			i = i + ft_strlen(dst) - old_len + 1;	
		}
	}
	return (dst);
}

char	*add_literal_str(char *dst, char *str, char quote)
{
	char	*dst;
	int		len;
	char 	*aux;

	len = ft_strchr(str, SINGLE_QUOTE) - str;
	aux = malloc((ft_strlen(dst) + len + 1) * sizeof(char));
	ft_strlcpy(aux, str, len);
	dst = ft_strjoin_freed(dst, aux);
	free(aux);
	return (dst);
}