/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:46:17 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/03 14:24:28 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	save_token(t_varparse *data)
{
	t_list	*node;
	char	*aux;
	
	aux = ft_strdup(data->tmp);
	if(!aux)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	node = ft_lstnew((void *)aux);
	if(!node)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	ft_lstadd_back(&data->tk_lst, node);
	ft_free2(&data->tmp);
	return (EXIT_SUCCESS);
}

int	handle_final_token(t_varparse *data)
{
	t_list	*node;
	char	*aux;

	aux = ft_strdup(data->tmp);
	ft_free2(&data->tmp);
	if (!aux)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	node = ft_lstnew((void *)aux);
	aux = NULL;
	if (!node)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	ft_lstadd_back(&data->tk_lst, node);
	return (EXIT_SUCCESS);
}

char	*add_literal_str(char *dst, char *str, char quote)
{
	int		len;
	char 	*aux;

	len = ft_strchr(str, quote) - str;
	aux = malloc((ft_strlen(dst) + len + 1) * sizeof(char));
	if (!aux)
		return (handle_error(ERR_MALLOC), NULL);
	ft_strlcpy(aux, str, len + 1);
	dst = ft_strjoin_freed(dst, aux);
	if (!dst)
		return (handle_error(ERR_MALLOC), NULL);
	ft_free(aux);
	return (dst);
}

char	*ft_add_char_freed(char *str, char c)
{
	char	*dst;

	dst = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!dst)
		return (handle_error(ERR_MALLOC), NULL);
	ft_strlcpy(dst, str, ft_strlen(str) + 1);
	dst[ft_strlen(str)] = c;
	dst[ft_strlen(str) + 1] = '\0';
	ft_free(str);
	return (dst);
}
