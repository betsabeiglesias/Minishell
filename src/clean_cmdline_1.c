/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmdline_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:06:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/26 19:46:54 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *clean_cmdline(char *str)
{
	t_cl_data	data;

	init_cl_data(&data);
	while(str[data.i] == SPACE)
		data.i++;
	while(str[data.i])
	{
		if (!data.tmp)
			data.tmp = ft_strdup("");
		if (str[data.i] == SINGLE_QUOTE)
			handle_quote(&data, str, SINGLE_QUOTE);
		else if ((str[data.i] == DOUBLE_QUOTE))
			handle_quote(&data, str, DOUBLE_QUOTE);
		else if (str[data.i] == SPACE)
			handle_space(&data, str);
		else
		{
			data.tmp = ft_add_char_freed(data.tmp, str[data.i]);
			data.i++;
		}
	}
	if (data.tmp)
		handle_final_tmp(&data);
	return (data.dst);
}

void	init_cl_data(t_cl_data *data)
{
	data->i = 0;
	data->old_len = 0;
	data->dst = ft_strdup("");
	data->tmp = NULL;
	return ;
}

void	handle_quote(t_cl_data *data, char *str, char quote)
{
	data->old_len = ft_strlen(data->tmp);
	data->tmp = add_literal_str(data->tmp, &str[data->i + 1], quote);
	data->i = data->i + ft_strlen(data->tmp) - data->old_len + 2;
	return ;
}

void	handle_space(t_cl_data *data, char *str)
{
	data->dst = ft_add_char_freed(data->dst, DOUBLE_QUOTE);
	data->dst = ft_strjoin_freed(data->dst, data->tmp);
	data->dst = ft_add_char_freed(data->dst, DOUBLE_QUOTE);
	if (data->tmp)
	{
		free(data->tmp);
		data->tmp = NULL;
	}
	data->dst = ft_add_char_freed(data->dst, SPACE);
	while(str[data->i] == SPACE)
		data->i++;
	return ;
}




















































/*
char *clean_string(char *str)
{
	char	*dst;
	int		i;
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
			dst = add_literal_str(dst, &str[i + 1], SINGLE_QUOTE);
			i = i + ft_strlen(dst) - old_len + 1;
		}
		else if (str[i] == DOUBLE_QUOTE)
		{
			old_len = ft_strlen(dst);
			dst = add_literal_str(dst, &str[i + 1], DOUBLE_QUOTE);
		}
		else
		{
			old_len = ft_strlen(dst);
			dst = add_literal_str(dst, &str[i], SPACE);
			i = i + ft_strlen(dst) - old_len + 1;	
		}
	}
	return (dst);
}

char	*add_literal_str(char *dst, char *str, char quote)
{
	int		len;
	char 	*aux;

	len = ft_strchr(str, quote) - str;
	aux = malloc((ft_strlen(dst) + len + 1) * sizeof(char));
	ft_strlcpy(aux, str, len);
	dst = ft_strjoin_freed(dst, aux);
	free(aux);
	return (dst);
}
*/