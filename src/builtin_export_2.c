/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:21:45 by binary            #+#    #+#             */
/*   Updated: 2024/12/18 20:27:52 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	export_no_args(t_mini *shell, int fd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		print_export(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	print_export(char *str, int fd)
{
	int	i;

	i = 0;
	if (check_varequal(str))
	{
		while (str[i] != '\0')
		{
			ft_putchar_fd(str[i], fd);
			if (str[i] == '=')
				ft_putchar_fd('\"', fd);
			i++;
		}
		ft_putchar_fd('\"', fd);
	}
	else
		ft_putstr_fd(str, fd);
}

int	len_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	ft_matdup(char **mat_dst, char **mat_src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		mat_dst[i] = ft_strdup(mat_src[i]);
		if (!mat_dst[i])
		{
			while (i > 0)
			{
				free(mat_dst[i]);
				i--;
			}
			free(mat_dst);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
