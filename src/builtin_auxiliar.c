/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_auxiliar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:30 by binary            #+#    #+#             */
/*   Updated: 2024/11/19 10:41:02 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t ft_strlen_variadic(int num_args, ...) 
{
	size_t len;
	char *str;
    int i;
	va_list args;
	
    len = 0;
    i = 0;
	va_start(args, num_args);
    while (i < num_args) 
	{
        str = va_arg(args, char *);
		if (str)
        	len += ft_strlen(str);
        i++;
    }
	va_end(args);
    return (len);
}

void concatenate_strings(int num_args, va_list args, char *result) 
{
    char *str;
    int i;
    	  
    result[0] = '\0';
    i = 0;
    while (i < num_args)
    {
        str = va_arg(args, char *);
		ft_strlcat(result, str, ft_strlen(result) + ft_strlen(str) + 1);
        i++;
    }
}

char *ft_strjoin_variadic(int num_args, ...) 
{
    va_list args;
    size_t len;
    char *result;
	
    va_start(args, num_args);
    len = ft_strlen_variadic(num_args, args);
    va_end(args);
    result = (char *)malloc((len + 1) * sizeof(char));
    if (!result)
		return (NULL);
	va_start(args, num_args);
	concatenate_strings(num_args, args, result);
	va_end(args);
    return (result);
}