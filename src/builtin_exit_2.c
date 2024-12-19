/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:24:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/19 19:48:51 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_exit(void)
{
	ft_putstr_fd(EXIT, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	ft_atoi_exit(char *str)
{
	int	nb;

	nb = ft_atoi(str);
	nb = nb % 256;
	return (nb);
}

int	ft_str_hasalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}
