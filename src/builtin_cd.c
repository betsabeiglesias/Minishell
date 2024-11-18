/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/18 21:39:55 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
int	builtin_cd(char **cmd_all)
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
}*/
/* testeo */
int	builtin_cd(char *cmd_all, t_mini *shell)
{
 	(void)cmd_all;
	cd_to_home(shell);
	return(EXIT_SUCCESS);
}
// seguir desarrollando
// int	builtin_cd(char **cmd_all, t_mini *shell)
// {
// 	if(!cmd_all[1])
// 		return(cd_to_home(shell));
// 	if (cmd_all[1] == ".." || cmd_all[1] == "-")
// 		cd_especial_cases 

// }


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

size_t ft_strlen_variadic(int num_args, ...) 
{
	size_t len;
	char *str;
    int i;
	va_list args;
	printf("entra en strlen variadic\n");
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

void concatenate_strings(int num_args, va_list args, char *result) 
{
    char *str;
    int i;
    
	printf("entra en concaneta variadic\n");
   
    result[0] = '\0';  // Asegúrate de que el resultado esté vacío
    i = 0;
    while (i < num_args)  // Restar 1 porque ya hemos pasado `result`
    {
        str = va_arg(args, char *);
		ft_strlcat(result, str, ft_strlen(result) + ft_strlen(str) + 1);
        i++;
    }
}

char *ft_strjoin_variadic(int num_args, ...) 
{
    va_list args;
    size_t len;
    char *result;
	printf("entra en join variadic\n");
    va_start(args, num_args);
    len = ft_strlen_variadic(num_args, args);
    va_end(args);

    result = (char *)malloc((len + 1) * sizeof(char));
    if (!result)
		return NULL;
	va_start(args, num_args);
	concatenate_strings(num_args, args, result);  // Pasar `result` primero
	va_end(args);
    return (result);
}
