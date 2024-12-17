/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_auxiliar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:39:30 by binary            #+#    #+#             */
/*   Updated: 2024/12/17 23:35:21 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlen_variadic(int num_args, ...)
{
	size_t	len;
	char	*str;
	int		i;
	va_list	args;

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

void	concatenate_strings(int num_args, va_list args, char *result)
{
	char	*str;
	int		i;

	result[0] = '\0';
	i = 0;
	while (i < num_args)
	{
		str = va_arg(args, char *);
		ft_strlcat(result, str, ft_strlen(result) + ft_strlen(str) + 1);
		i++;
	}
}

char	*ft_strjoin_variadic(int count, ...)
{
	va_list	args;
	size_t	total_len;
	char	*result;
	int		temp_count;

	total_len = 0;
	va_start(args, count);
	temp_count = count;
	while (count-- > 0)
	{
		total_len += ft_strlen(va_arg(args, char *));
	}
	va_end(args);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	va_start(args, count);
	while (temp_count -- > 0)
	{
		ft_strlcat(result, va_arg(args, char *), total_len + 1);
	}
	va_end(args);
	return (result);
}

int	is_builtin(char **cmd)
{
	if (cmd == NULL)
		return (0);
	if (is_identical_str(cmd[0], ENV))
		return (1);
	if (is_identical_str(cmd[0], EXIT))
		return (1);
	if (is_identical_str(cmd[0], "echo"))
		return (1);
	if (is_identical_str(cmd[0], PWD))
		return (1);
	if (is_identical_str(cmd[0], CD))
		return (1);
	if (is_identical_str(cmd[0], EXPORT))
		return (1);
	if (is_identical_str(cmd[0], UNSET))
		return (1);
	return (0);
}
