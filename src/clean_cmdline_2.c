/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmdline_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:46:17 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/26 19:46:46 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_final_tmp(t_cl_data *data)
{
	data->dst = ft_add_char_freed(data->dst, DOUBLE_QUOTE);
	data->dst = ft_strjoin_freed(data->dst, data->tmp);
	data->dst = ft_add_char_freed(data->dst, DOUBLE_QUOTE);
	return ;
}

char	*add_literal_str(char *dst, char *str, char quote)
{
	int		len;
	char 	*aux;

	len = ft_strchr(str, quote) - str;
	aux = malloc((ft_strlen(dst) + len + 1) * sizeof(char));
	if (!aux)
		return (NULL);
	ft_strlcpy(aux, str, len + 1);
	dst = ft_strjoin_freed(dst, aux);
	if (!dst)
		return (NULL);
	free(aux);
	return (dst);
}

char	*ft_add_char_freed(char *str, char c)
{
	char	*dst;

	dst = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, str, ft_strlen(str) + 1);
	dst[ft_strlen(str)] = c;
	dst[ft_strlen(str) + 1] = '\0';
	free(str);
	return (dst);
}
