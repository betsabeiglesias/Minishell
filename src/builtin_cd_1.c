/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/23 16:25:28 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
int	builtin_cd(char **cmd_all, t_mini *shell)
{
	if(!cmd_all[1])
		return(cd_to_home(shell), EXIT_SUCCESS);
	if (!ft_strncmp(cmd_all[1], "..", 2) || !ft_strncmp(cmd_all[1], "-", 1))
		return(cd_especial_cases(cmd_all, shell), EXIT_SUCCESS);
	if(chdir(cmd_all[1]) == 0)
		return(EXIT_SUCCESS);
	return (handle_error(ERR_ACCESS), EXIT_FAILURE); 
}

// REVISAR MENSAJES DE ERRORES DE RETORNO
int	cd_to_home(t_mini *shell)
{
	char	*home_path;
	char	*dir_to_save;

	home_path = find_env("HOME", shell);
	if (home_path == NULL)
		return(printf("ERROR AL ACCEDER A HOME\n"), EXIT_FAILURE);
	dir_to_save = getcwd(NULL, 0);
	if(!dir_to_save)
		return(printf("ERROR AL GUARDAR DIR\n"), EXIT_FAILURE);
	if(update_dir_env("OLDPWD", dir_to_save, shell) != 0)
		return(printf("ERROR AL UPDATE OLDPWD\n"), EXIT_FAILURE);
	if (chdir(home_path) != 0)
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	dir_to_save = getcwd(NULL, 0);
	update_dir_env("PWD", dir_to_save, shell);
	free(dir_to_save);
	return (EXIT_SUCCESS);
}

char *find_env(char *str, t_mini *shell)
{
	int i;
	int len;
	
	i = 0;
	len = ft_strlen(str);
	while(shell->env[i])
	{
		if(!ft_strncmp(str, shell->env[i], len) && shell->env[i][len] == '=')
		{
			printf("FIND ENV: %s\n", shell->env[i] + len + 1);
			return(shell->env[i] + len + 1);
		}
		i++;	
	}
	return(NULL);
}

int	update_dir_env(char *dir, char *new_value, t_mini *shell)
{
	int		i;
	int		len;
	char	*new_var;
	
	printf("entra en update\n");
	i = 0;
	len = ft_strlen(dir);
	while (shell->env[i])
	{
		if(!ft_strncmp(dir, shell->env[i], len) && shell->env[i][len] == '=')
		{
			new_var = ft_strjoin_variadic(3, dir, "=", new_value);
			printf("DIR: %s\n\n", dir);
			printf("NEW VALUE: %s\n\n", new_value);
			printf("NEW VAR: %s\n\n", new_var);
			if(!new_var)
				return(handle_error(ERR_MALLOC), EXIT_FAILURE);
			shell->env[i] = new_var;
				return(EXIT_SUCCESS);
		}
		i++;	
	}
	return(EXIT_SUCCESS);
}
*/