/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:29:01 by binary            #+#    #+#             */
/*   Updated: 2024/12/16 23:31:01 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	change_value_varenv(char *varen, char *new_value, t_mini *shell)
{
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(varen, "=");
	if (!temp)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	new_var = ft_strjoin(temp, new_value);
	if (!new_var)
	{
		free(temp);
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	}
	free(temp);
	if (update_env(varen, new_var, shell))
	{
		free(new_var);
		return (EXIT_FAILURE);
	}
	free(new_var);
	return (EXIT_SUCCESS);
}
