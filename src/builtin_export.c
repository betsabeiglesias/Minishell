/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:56:51 by binary            #+#    #+#             */
/*   Updated: 2024/11/13 11:59:03 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_export(t_mini *shell, t_list *tk_lst)
{
	int args;
	args = 1;
	if(!((char *)(tk_lst->content))[args])
	{
		printf("Aquí añadir variable\n");
		// str es la variable nueva, modificar cuando esté full_cmd
		if(export_args(str, shell))
			return(EXIT_FAILURE);
		return(EXIT_SUCCESS);
	}
	export_no_args(shell);
	return(EXIT_SUCCESS);

}
int	export_args(char *str, t_mini *shell)
{
	size_t	len;
	size_t	i;
	char	**new_env;
	
	len = ft_matsize(shell->env);
	i = 0;
	new_env = malloc(sizeof(char *) * (len + 2));
	if(!new_env)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	while(i < len)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if(!new_env[i])
			return(handle_error(ERR_MALLOC), EXIT_FAILURE);
		i++;
	}
	new_env[i + 1] = ft_strdup(str);
	if(!new_env[i])
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	new_env[i + 2] = '\0';
	ft_free_mat_str(shell->env, len);
	shell->env = new_env;
	return(EXIT_SUCCESS);
}

void	export_no_args(t_mini *shell)
{
	int	i;
	i = 0;
	while(shell->env[i])
	{
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		print_export(shell->env[i]);
		ft_putstr_fd("\n", STDIN_FILENO);
		i++;
	}
}

void	print_export(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		ft_putchar_fd(str[i], STDIN_FILENO);
		if (str[i] == '=')
			ft_putchar_fd('\"',STDIN_FILENO);
		i++;
	}
	ft_putchar_fd('\"',STDIN_FILENO);
}
