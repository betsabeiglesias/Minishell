/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/13 13:17:53 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_cd(char **cmd)
{
	if (chdir(cmd[1]) != 0)
	{
		printf("no se cambió\n");
		return (1);
	}
	else
	{
		printf("Se cambió al dir; %s\n", cmd[1]);
		builtin_pwd();
	}
	return (0);
}