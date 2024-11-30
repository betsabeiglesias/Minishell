/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_auxiliar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:30 by binary            #+#    #+#             */
/*   Updated: 2024/11/30 18:40:43 by aolabarr         ###   ########.fr       */
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

char *ft_strjoin_variadic(int count, ...)
{
    va_list args;
    size_t total_len;
    char *result;
    int i;
    
    i = 0;
    total_len = 0;
    va_start(args, count);
    while(i < count)
    {
        total_len += ft_strlen(va_arg(args, char *));
        i++;
    }
    va_end(args);
    result = malloc(total_len + 1);
    if (!result)
        return NULL;
    result[0] = '\0';
    va_start(args, count);
    i = 0;
    while(i < count)
    {
        ft_strlcat(result, va_arg(args, char *), total_len + 1);
        i++;
    }
    va_end(args);
    return (result);
}


int     is_builtin(char *cmd)
{
    if (!ft_strncmp(cmd, ENV, ft_strlen(ENV)) && (ft_strlen(cmd) == ft_strlen(ENV)))
		return (1);
    if (!ft_strncmp(cmd, EXIT, ft_strlen(EXIT)) && (ft_strlen(cmd) == ft_strlen(EXIT)))
        return (1);
    //if (!ft_strncmp(cmd, "echo", ft_strlen("echo")) && (ft_strlen(cmd) == ft_strlen("echo")))
    //    return (1);
    if (!ft_strncmp(cmd, PWD, ft_strlen(PWD)) && (ft_strlen(cmd) == ft_strlen(PWD)))
        return (1);
     if (!ft_strncmp(cmd, CD, ft_strlen(CD)) && (ft_strlen(cmd) == ft_strlen(CD)))
        return (1);
    if (!ft_strncmp(cmd, EXPORT, ft_strlen(CD)) && (ft_strlen(cmd) == ft_strlen(EXPORT)))
        return (1);
    return (0);
}