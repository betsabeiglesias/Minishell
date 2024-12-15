# include "../inc/minishell.h"

int cd_especial_cases(t_exec *node, t_mini *shell)
{
	if (!ft_strncmp(node->cmd_all[1], "-", 1))
		return(go_to_oldpwd(shell), EXIT_SUCCESS);
	if (is_identical_str(node->cmd_all[1], ".."))
		return(go_to_previousdir(shell), EXIT_SUCCESS);
	if (!ft_strncmp(node->cmd_all[1], "../", 3))
	{
		relative_route(node, shell);
		return(EXIT_SUCCESS);
	}
	return(EXIT_FAILURE);
}

int go_to_oldpwd(t_mini *shell)
{
    char *dir_to_save;
    char *oldpwd_dir;

	dir_to_save = getcwd(NULL, 0);
	if(!dir_to_save)
		return(handle_error(ERR_GETWD), EXIT_FAILURE);
	oldpwd_dir = ft_strdup(find_value_varenv("OLDPWD", shell));
	if(!oldpwd_dir)
	{
		free(dir_to_save);
		return(handle_error(ERR_OLDPWD), EXIT_FAILURE);
	}
	if (chdir(oldpwd_dir) != 0)
	{
		free(dir_to_save);
		free(oldpwd_dir);
		return (handle_error(ERR_CHDIR), EXIT_FAILURE);
	}
	update_dir_env("OLDPWD", dir_to_save, shell);
	update_dir_env("PWD", oldpwd_dir, shell);
	free(dir_to_save);
	free(oldpwd_dir);
	return(EXIT_SUCCESS);
}

int go_to_previousdir(t_mini *shell)
{
    char *dir_to_save;
    char *previous_dir;

	dir_to_save = getcwd(NULL, 0);
	if(!dir_to_save)
		return(handle_error(ERR_GETWD), EXIT_FAILURE);
	previous_dir = get_previous_dir(dir_to_save);
	if(!previous_dir)
	{
		free(dir_to_save);
		return(handle_error(ERR_GETWD), EXIT_FAILURE);
	}
	if (chdir(previous_dir) != 0)
	{
		free(dir_to_save);
		free(previous_dir);
		return (handle_error(ERR_CHDIR), EXIT_FAILURE);
	}
	update_dir_env("OLDPWD", dir_to_save, shell);
	update_dir_env("PWD", previous_dir, shell);
	free(dir_to_save);
	free(previous_dir);
	return(EXIT_SUCCESS);
}

char	*get_previous_dir(char *str)
{
	int	i;
	int len;
	char *result;

	i = 0;
	len = strlen(str);
	result = NULL;
	while (len >= 0)
	{
		if (str[len] == '/' && len == 0)
		{	
			result = ft_strdup("/");
			return (result);
		}
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
int relative_route(t_exec *node, t_mini *shell)
{
	char	*previous_dir;
	char	*current_dir;
	char	*obj_dir;

	current_dir = getcwd(NULL, 0);
	if(!current_dir)
		return(handle_error(ERR_GETWD), EXIT_FAILURE);
	previous_dir = get_previous_dir(current_dir);
	if(!current_dir)
	{
		free (current_dir);
		return(handle_error(ERR_GETWD), EXIT_FAILURE);
	}
	obj_dir = ft_strjoin_variadic(3, previous_dir, "/", node->cmd_all[1]+3);
	if (chdir(obj_dir) != 0)
	{
		free(current_dir);
		free(previous_dir);
		return (handle_error(ERR_CHDIR), EXIT_FAILURE);
	}
	update_dir_env("OLDPWD", current_dir, shell);
	update_dir_env("PWD", obj_dir, shell);
	free(current_dir);
	free(previous_dir);
	free(obj_dir);
	return(EXIT_SUCCESS);
}
