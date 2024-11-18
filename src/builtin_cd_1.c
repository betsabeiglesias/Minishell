# include "../inc/minishell.h"

int cd_especial_cases(char **cmd_all, t_mini *shell)
{
    if(cmd_all[1] == "-")
        go_to_olpwd(shell);

}

int go_to_oldpwd(t_mini *shell)
{
    char *dir_to_save;
    char *previous_dir;

    dir_to_save = getcwd(NULL, 0);
    previous_dir = find_env("OLDPWD", shell);
    if(!dir_to_save)
		return(printf("ERROR AL GUARDAR DIR\n"), EXIT_FAILURE);
    if (chdir(previous_dir) != 0)
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
    update_dir_env("OLDPWD", dir_to_save, shell);
    update_dir_env("PWD", previous_dir, shell);
    return(EXIT_SUCCESS);
}