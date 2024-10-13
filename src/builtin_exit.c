/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:24:56 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/13 13:28:48 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void builtin_exit(char **cmd)
{
	if(!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
		exit;
}