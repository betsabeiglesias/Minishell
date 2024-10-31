/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:06:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/31 19:52:54 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*tokenization(char *str)
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
		{
			if(!save_token(&data, str))
				return(NULL);
		}
		else
			handle_char(&data, str);
	}
	if (data.tmp)
		handle_final_tmp(&data);
	return (data.tk_lst);
}

void	init_cl_data(t_cl_data *data)
{
	data->i = 0;
	data->old_len = 0;
	data->tmp = NULL;
	data->tk_lst = NULL;
	return ;
}

void	handle_quote(t_cl_data *data, char *str, char quote)
{
	data->old_len = ft_strlen(data->tmp);
	data->tmp = add_literal_str(data->tmp, &str[data->i + 1], quote);
	data->i = data->i + ft_strlen(data->tmp) - data->old_len + 2;
	return ;
}
void	handle_char(t_cl_data *data, char *str)
{
	data->tmp = ft_add_char_freed(data->tmp, str[data->i]);
	data->i++;
	return ;
}

char	*save_token(t_cl_data *data, char *str)
{
	t_list	*node;
	char	*aux;
	
	aux = ft_strdup(data->tmp);
	if(!aux)
		return(handle_error(ERR_MALLOC), NULL);
	node = ft_lstnew(aux);
	if(!node)
		return(handle_error(ERR_MALLOC), NULL);
	ft_lstadd_back(&data->tk_lst, node);
	if (data->tmp)
	{
		free(data->tmp);
		data->tmp = NULL;
	}
	while(str[data->i] == SPACE)
		data->i++;
	return (NO_NULL);
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