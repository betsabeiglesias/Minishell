/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:06:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/01 12:30:35 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*tokenization(char *str)
{
	t_varparse	data;

	init_var_parse(&data);
	while(str[data.i] == SPACE)
		data.i++;
	while(str[data.i])
	{
		if (!handle_token(&data, str))
			return (NULL);
	}
	if (data.tmp)
		handle_final_token(&data);
	return (data.tk_lst);
}

char	*handle_token(t_varparse *data, char *str)
{
	if (!data->tmp)
		data->tmp = ft_strdup("");
	if (!data->tmp)
		return (handle_error(ERR_MALLOC), NULL);
	if (str[data->i] == SINGLE_QUOTE)
		handle_quote(data, str, SINGLE_QUOTE);
	else if ((str[data->i] == DOUBLE_QUOTE))
		handle_quote(data, str, DOUBLE_QUOTE);
	else if (str[data->i] == SPACE)
	{
		if(!save_token(data, str))
			return(NULL);
	}
	else
		handle_char(data, str);
	return (NO_NULL);
}

void	init_var_parse(t_varparse *data)
{
	data->i = 0;
	data->old_len = 0;
	data->tmp = NULL;
	data->tk_lst = NULL;
	return ;
}

void	handle_quote(t_varparse *data, char *str, char quote)
{
	data->old_len = ft_strlen(data->tmp);
	data->tmp = add_literal_str(data->tmp, &str[data->i + 1], quote);
	data->i = data->i + ft_strlen(data->tmp) - data->old_len + 2;
	return ;
}
void	handle_char(t_varparse *data, char *str)
{
	data->tmp = ft_add_char_freed(data->tmp, str[data->i]);
	data->i++;
	return ;
}
