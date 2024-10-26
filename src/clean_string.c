/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:06:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/26 18:06:48 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *clean_string(char *str)
{
	int		i;
	char	*dst;
	char	*tmp;
	int		old_len;

	i = 0;
	dst = ft_strdup("");
	tmp = NULL;
	while(str[i] == SPACE)
		i++;
	while(str[i])
	{
		if (!tmp)
			tmp = ft_strdup("");
		if (str[i] == SINGLE_QUOTE)
		{
			old_len = ft_strlen(tmp);
			tmp = add_literal_str(tmp, &str[i + 1], SINGLE_QUOTE);
			i = i + ft_strlen(tmp) - old_len + 2;
		}
		else if ((str[i] == DOUBLE_QUOTE))
		{
			old_len = ft_strlen(tmp);
			tmp = add_literal_str(tmp, &str[i + 1], DOUBLE_QUOTE);
			i = i + ft_strlen(tmp) - old_len + 2;
		}
		else if (str[i] == SPACE)
		{
			dst = ft_strjoin_freed(dst, tmp);
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			dst = ft_add_char_freed(dst, SPACE);
			while(str[i] == SPACE)
				i++;
		}
		else
		{
			tmp = ft_add_char_freed(tmp, str[i]);
			i++;
		}
	}
	dst = ft_strjoin_freed(dst, tmp);
	return (dst);
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