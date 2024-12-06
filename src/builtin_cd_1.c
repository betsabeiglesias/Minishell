/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/02 12:12:30 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

void print_env(t_mini *shell)
{
    int i = 0;
    printf("Contenido actual de shell->env:\n");
    while (shell->env[i])
    {
        printf("env[%d]: %s\n", i, shell->env[i]);
        i++;
    }
	// printf("DIRECCIÓN MEMORIA SHELL ENV: %p\n", shell->env);
}

int	builtin_cd(t_exec *node, t_mini *shell)
{
	if(!node->cmd_all[1])
		return(cd_to_home(shell), EXIT_SUCCESS);
	if (!ft_strncmp(node->cmd_all[1], "..", 2) || !ft_strncmp(node->cmd_all[1], "-", 1))
		return(cd_especial_cases(node, shell), EXIT_SUCCESS);
	if(chdir(node->cmd_all[1]) == 0)
		return(EXIT_SUCCESS);
	return (handle_error(ERR_ACCESS), EXIT_FAILURE); 
}

// REVISAR MENSAJES DE ERRORES DE RETORNO
int	cd_to_home(t_mini *shell)
{
	char	*home_path;
    char	*dir_to_save;

	home_path = find_value_varenv("HOME", shell);
    if (home_path == NULL)
    {
        printf("Error accessing HOME environment variable.\n");
        return EXIT_FAILURE;
    }
    dir_to_save = getcwd(NULL, 0);
    if (!dir_to_save)
    {
        printf("Error getting current working directory.\n");
        return EXIT_FAILURE;
    }
    if (change_value_varenv("OLDPWD", dir_to_save, shell) != 0)
    {
        printf("Error updating OLDPWD.\n");
        free(dir_to_save);
        return EXIT_FAILURE;
    }
    if (chdir(home_path) != 0)
    {
        handle_error(ERR_ACCESS);
        free(dir_to_save);
        return EXIT_FAILURE;
    }
    free(dir_to_save);
    dir_to_save = getcwd(NULL, 0);
    if (!dir_to_save)
    {
        printf("Error getting new working directory after chdir.\n");
        return EXIT_FAILURE;
    }
    if (change_value_varenv("PWD", dir_to_save, shell) != 0)
    {
        free(dir_to_save);
        return EXIT_FAILURE;
    }
	//print_env(shell);
    free(dir_to_save);
    return EXIT_SUCCESS;
}

char *find_value_varenv(char *str, t_mini *shell)
{
	int i;
	int len;
	
	i = 0;
	len = ft_strlen(str);
	while(shell->env[i])
	{
		if(!ft_strncmp(str, shell->env[i], len) && shell->env[i][len] == '=')
		{
			// printf("FIND ENV: %s\n", shell->env[i] + len + 1);
			return(shell->env[i] + len + 1);
		}
		i++;	
	}
	return(NULL);
}


/* ANALIZAR SI LA VARIABLE NO ESTÁ EN ENV */
int	update_dir_env(char *dir, char *new_value, t_mini *shell)
{
	int		i;
	int		len;
	char	*new_var;
	
	i = 0;
	len = ft_strlen(dir);
	//printf("%i LEN \n", len);
	while (shell->env[i])
	{
		if(!ft_strncmp(dir, shell->env[i], len) && shell->env[i][len] == '=')
		{
			new_var = ft_strjoin_variadic(3, dir, "=", new_value);
			// printf("DIR: %s\n\n", dir);
			// printf("NEW VALUE: %s\n\n", new_value);
			// printf("NEW VAR: %s\n\n", new_var);
			if(!new_var)
				return(handle_error(ERR_MALLOC), EXIT_FAILURE);
			// printf("Antes: %s\n", shell->env[i]);
			free(shell->env[i]);
			shell->env[i] = new_var;
			// printf("Después: %s\n", shell->env[i]);
			// printf("Variable actualizada: %s\n", new_var);
			// print_env(shell);
			return(EXIT_SUCCESS);
		}
		i++;	
	}
	printf("Variable %s no encontrada en shell->env\n", dir);
	return(EXIT_SUCCESS);
}

int	update_env(char *var_name, char *new, t_mini *shell)
{
	size_t	i;
	char	*temp;
	int 	len;

	i = 0;
	len = ft_strlen(var_name);
	while (shell->env[i])
	{
		if (!ft_strncmp(var_name, shell->env[i], len) && shell->env[i][len] == '=')
		{
			temp = shell->env[i];
			shell->env[i] = ft_strdup(new);
			if (!shell->env[i])
				return (handle_error(ERR_MALLOC), EXIT_FAILURE);
			free(temp);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
int	change_value_varenv(char *varen, char *new_value, t_mini *shell)
{
	char	*set_new;
	char	*new_var;
	char	*temp;

	set_new = ft_strdup(new_value);
	if (!set_new)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	temp = ft_strjoin(varen, "=");
	if (!temp)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	new_var = ft_strjoin(temp, set_new);
	if (!new_var)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	free(temp);
	if (update_env(varen, new_var, shell))
		return (EXIT_FAILURE);
	return (free(set_new), EXIT_SUCCESS);
}