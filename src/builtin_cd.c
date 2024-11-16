/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/16 17:01:30 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
}
int	builtin_cd(char **cmd_all, t_mini *shell)
{
	if(!cmd_all[1])
		return(cd_to_home(shell));

}

// REVISAR MENSAJES DE ERRORES DE RETORNO

int	cd_to_home(t_mini *shell)
{
	int		i;
	char	*home_path;
	char	*dir_to_save;

	i = 0;
	home_path = find_env("HOME", shell);
	if (home_path == NULL)
		return(printf("ERROR AL ACCEDER A HOME\n"), EXIT_FAILURE);
	dir_to_save = getcwd(NULL, 0);
	if(!dir_to_save)
		return(printf("ERROR AL GUARDAR DIR\n"), EXIT_FAILURE);
	//OLDPWD TIENE QUE SER dir_to_save
	//PWD



	if (chdir(home_path) == 0)
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
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
			return(shell->env[i] + len + 1);
		i++;	
	}
	return(NULL);
}

int	update_dir_env(char *dir, char *new_value, t_mini *shell)
{
	int	i;
	int len;
	
	i = 0;
	len = ft_strlen(dir);
	while (shell->env[i])
	{
		if(!ft_strncmp(dir, shell->env[i], len) && shell->env[i][len] == '=')
		{
			new_var = ft_strjoin(dir, "=");


		}
		i++;	
	}
	return(NULL);

}

char *ft_strjoin_variadic(int count, char *str)
{
	va_list 	args;
	va_start	(args, count);
	size_t	len;
	int		i;
	char	*result;

	len = 0;
	i = 0;
	while(i < count)
	{
		char *s = va_arg(args, const char *);
        len += ft_strlen(s);
		i++;
    }

    // Reservar memoria para la cadena concatenada
    result = (char *)malloc((len + 1) * sizeof(char));
    if (!result)
    {
        va_end(args);
        return NULL;
    }
    result[0] = '\0'; 
    va_start(args, count);
	i = 0; 
    while(i < count)
    {
        const char *s = va_arg(args, const char *);
        ft_strlcat(result, s, len + 1); // Concatenar la cadena
		i++;
    }

    va_end(args);
    return result;
}