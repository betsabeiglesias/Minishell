/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:20:26 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/13 13:18:55 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*cambiar la recpeción a un doble puntero, implementar la opción -n*/
/* la opción -n evita el salto de línea que hace shell al finalizar echo*/

void	builtin_echo(char **cmd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (!ft_strncmp(cmd[i], "-n", ft_strlen(cmd[1])))
	{
		i++;
		flag = true;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		i++;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
// int main (int argc, char **argv)
// {
//     (void) argc;
//     builtin_echo(argv);
//     return(0);
// }