/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:20:26 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/12 13:42:10 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*cambiar la recpeción a un doble puntero, implementar la opción -n*/
/* la opción -n evita el salto de línea que hace shell al finalizar echo*/

void    builtin_echo (char *str)
{
    int i;

    i = 0;

    while (str[i])
    {
        ft_putchar_fd(str[i], STDOUT_FILENO);
        i++;
    }
    ft_putchar_fd('\n', STDOUT_FILENO);
}

int main (int argc, char **argv)
{
    (void) argc;
    

    builtin_echo(argv[1]);
    return(0);
}