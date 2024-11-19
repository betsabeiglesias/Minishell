# include "../inc/minishell.h"

int cd_especial_cases(char **cmd_all, t_mini *shell)
{
    if (cmd_all[1] == "-")
    	return(go_to_olpwd(shell), EXIT_SUCCESS);
	if (cmd_all[1] == "..")
		return(go_to_previousdir(shell), EXIT_SUCCESS);
	return(EXIT_FAILURE);
}

int go_to_oldpwd(t_mini *shell)
{
    char *dir_to_save;
    char *oldpwd_dir;

	dir_to_save = getcwd(NULL, 0);
	oldpwd_dir = find_env("OLDPWD", shell);
	if(!dir_to_save)
		return(printf("ERROR AL GUARDAR DIR\n"), EXIT_FAILURE);
	if (chdir(oldpwd_dir) != 0)
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	update_dir_env("OLDPWD", dir_to_save, shell);
	update_dir_env("PWD", oldpwd_dir, shell);
	return(EXIT_SUCCESS);
}

int go_to_previousdir(t_mini *shell)
{
    char *dir_to_save;
    char *previous_dir;

	dir_to_save = getcwd(NULL, 0);
	previous_dir = get_previous_dir(find_env("OLDPWD", shell));
	if(!dir_to_save)
		return(printf("ERROR AL GUARDAR DIR\n"), EXIT_FAILURE);
	if (chdir(previous_dir) != 0)
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	update_dir_env("OLDPWD", dir_to_save, shell);
	update_dir_env("PWD", previous_dir, shell);
	return(EXIT_SUCCESS);
}

char	*get_previous_dir(char *str)
{
	int	i;
	int len;
	char *result;

	i = 0;
	len = strlen(str);
	while (len >= 0)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	result = malloc(sizeof(char) * len + 1);
	if(!result)
		return(handle_error(ERR_MALLOC), NULL);
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return(result);
}