/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:28:14 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/14 19:39:30 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/* ************************************************************************** */


#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//MAIN
void	new_prompt(t_mini *shell, t_list *exe_lst);
void free_to_prompt(t_list *exe_lst, t_mini *shell);

//AUX
int     ft_print_lst(t_list *list);
int     ft_print_cmd_lst(t_list *cmd_lst);
void    print_cmd_all(char **cmd_all);

// CHECK SYNTAX 1
int		syntax_check(char*str);
int		check_quotes(char *str);
int		check_extrems(char *str);
void    new_quote_status(bool *s_quote, bool *d_quote, int i, char *str);

// CHECK UTILS
int		is_space(char c);
int		is_valid_metachar(char c);
int		is_str_space(char *str);
int     is_redir_metachar(char c);

// HANDLE ERROR
int		handle_error(int error_type);
void    handle_error_continue(int error_type);

//PARSE
t_list	*parse(t_mini *shell);
int syntax_check_on_tokens(t_list *tk_lst);
int is_str_metachar(char *str);

//SYNTAX CHECK 2
int		check_metachar_separate(char *str);
int		do_check(char *str, int i);
int		check_pipe_separate(char *str, int i);
int		check_redir_separate(char *str, int i, char c);
int		do_redir_check(char *str,int i, char c);

//SYNTAX CHECK 3
int     check_metachar_consecutive(char *str);
int     do_check_consecutive(char *str, int i);

//TOKENIZATION_1
t_list	*tokenization(char *str);
void	init_var_parse(t_varparse *data);
void	handle_quote(t_varparse *data, char *str, char quote);
void	handle_char(t_varparse *data, char *str);
int     handle_token(t_varparse *data, char *str);

//TOKENIZATION_2
int     save_token(t_varparse *data);
int     handle_final_token(t_varparse *data);
char	*add_literal_str(char *dst, char *str, char quote);
char	*ft_add_char_freed(char *str, char const c);

//FREE
void	lst_clear_token_content(t_list *lst);
void	free_shell(t_mini *shell);
void    handle_free(t_mini shell, int error);
void	ft_free_mat_int(int **mat, int size);
void    lst_clear_exec(t_list *lst);
void	ft_free_mat_int(int **mat, int size);
void	ft_free_v(void *str);
void    free_node_exec(t_exec *node);

// SIGNALS
void	setup_signal_handlers_shell(void);
void    setup_signal_handlers_fork(void);
void    setup_signal_handlers_builtin(void);
void    handle_signal_father(int signum);
int		handle_eof_interactive(char *str);
void    handle_signal_child(int signum);
void	handle_signal_builtin(int signum);

//EXPANSION_1
int		insert_expanded_var (char **cmd_line, t_varenv *var);
bool	is_expansible(char *cmd_line, int i);
int		len_var(char *cmd_line, int i);
int     valid_char_env(char c);
int		get_var_env(t_mini *mini, t_varenv *var);

//EXPANSION_2
char	*do_expansion(t_mini *shell);
int		init_varen (t_varenv *var, char *cmd_line, int i);
void	clean_varen (t_varenv *var);
int		len_var(char *cmd_line, int i);
int     print_exitstatus(char **input, int i);

// ENVIROMENT
int		init_env(char **envp, t_mini *shell);
int		get_my_env(char **envp, t_mini *shell);
int	    exist_oldpwd(char **env);
void	free_env(t_mini *shell);
void	free_mini(t_mini *shell);

// BUILT_ENV_EXIT_ECHO (en archivos separados)
int		builtin_echo(t_exec *node, int fd);
int		builtin_exit(t_exec *node);
int		builtin_env(t_mini *shell, int fd);

// BUILT_AUX_EXIT
void	print_exit();
int		ft_atoi_exit(char *str);
int		ft_str_hasalpha(char *str);

// BUILTIN_PWD
int		builtin_pwd(int fd);
int		handle_exec_onlybuilt(t_exec *node, t_mini *shell);
int     execute_builtin(t_exec *node, t_mini *shell);
t_fd	*do_redir_built(t_exec *node);


// BUILTIN_AUXILIAR
size_t  ft_strlen_variadic(int num_args,...);
void    concatenate_strings(int num_args, va_list args, char *result);
char    *ft_strjoin_variadic(int num_args, ...);
int		is_builtin(char **cmd);

// BUILTIN_CD_1
int		builtin_cd(t_exec *node, t_mini *shell);
int     cd_to_home(t_mini *shell);  
char    *find_value_varenv(char *str, t_mini *shell);
int	    change_value_varenv(char *varen, char *new_value, t_mini *shell);
int     update_dir_env(char *dir, char *new_value, t_mini *shell);
int	    update_env(char *var_name, char *new, t_mini *shell);

// BUILTIN_AUXILIAR
size_t  ft_strlen_variadic(int num_args,...);
void    concatenate_strings(int num_args, va_list args, char *result);
char    *ft_strjoin_variadic(int num_args, ...);
void print_env(t_mini *shell);

// BUILTIN_CD_2
int 	cd_especial_cases(t_exec *node, t_mini *shell);
int     go_to_oldpwd(t_mini *shell);
int     go_to_previousdir(t_mini *shell);
char	*get_previous_dir(char *str);
int		relative_route(t_exec *node, t_mini *shell);

// BUILTIN_UNSET
int     builtin_unset(t_exec *node, t_mini *shell);
int		is_var_name(char *str, char *mini_var);
int	    new_reduced_size_env(t_exec *node, t_mini *shell);

// BUILTIN_EXPORT
int     builtin_export(t_exec *node, t_mini *shell, int fd);
int     change_var_value(char *str, t_mini *shell);
int     len_var_name(char *str);
int		export_args(char *str, t_mini *shell);
int     add_newvar(char *str, t_mini *shell);
void	export_no_args(t_mini *shell, int fd);
void	print_export(char *str, int fd);
int     check_namevar(char *str);

// INIT_DATA
int     init_shell(t_mini *shell, char **envp);
int     get_all_paths(t_mini *shell);
t_exec  *init_cmd_node(void);
int     **ft_malloc_mat_int(int x, int y, int size);

//COMMAND_LIST_1

int     handle_redir(t_list *tk_lst, t_exec *node, char *redir);
int     read_stdin(t_exec *node, char *delimiter);
t_list	*create_execution_list(t_list *tk_lst, t_mini *shell);
int     create_outfile(t_exec *node, char *redir);
void    handle_all_redir(t_list *tk_lst, int *is_redir, t_exec *node);
int     is_cmd_executable(char **cmd_all);
void	handle_get_path(t_exec *node, t_mini *shell);
int     handle_pipe(t_list *tk_lst, t_exec *node, t_mini *shell, t_list **exe_lst);
t_list  *jump_to_next_token(int is_redir, t_list *tk_lst);
//void    init_variables(t_exec *node, t_mini *shell);
t_exec  *init_variables(t_exec *node, t_mini *shell);
/* ************************************************************************** */

//COMMAND_LIST_2
char	*get_path(char **all_paths, char *cmd);
int     handle_commands(t_list *tk_lst, t_exec *node);
char    **add_token_to_cmd(char **cmd_all, char *str);
int     save_exe_node(t_list **exe_lst, t_exec *exe_node);
int     handle_last_save_node(t_list **exe_lst, t_exec **node, t_mini *shell);

// EXECUTION
int     init_execution(t_list *exe_lst, t_mini *shell);
int     exe_child(t_exec *node, int child, int num_procs, t_mini *shell);
int     wait_childs(t_mini *shell, int num_procs);
int     **create_pipes(int num_procs);
void	close_pipes(t_mini *shell, int num_procs);
int     builtin_count(t_list *exe_lst);
int     do_redirections(t_exec *node, int child, int num_procs, t_mini *shell);
int     create_here_doc_file(char *heredoc_content);
int     do_redirections_continue(t_exec *node, int fd_in, int fd_out);
void	get_exit_status(int *status, int i);

//COMMAND_LIST_AUX
int     is_str_pipe(char *str);
int     is_str_redir(char *str, char *redir);
int     is_identical_str(char *str1, char *str2);

#endif