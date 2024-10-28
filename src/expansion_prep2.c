/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_prep2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/28 15:06:04 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	insert_expanded_var(char **cmd_line, t_varenv *var)
{
	int 	old_len;
	int		new_len;
	int		exp_var_len;
	char	*new_line;

	old_len = ft_strlen(*cmd_line);
	exp_var_len = ft_strlen(var->var_expanded);
	new_len = old_len - var->len + exp_var_len;
	new_line = malloc(sizeof(char) * (new_len + 1));
	if (new_line == NULL)
		return ;
	ft_strlcpy(new_line, *cmd_line, var->start);
	ft_strlcat(new_line, var->var_expanded, new_len + 1);
	ft_strlcat(new_line, (*cmd_line + var->start + var->len), new_len + 1);
	clean_varen(var);
	free(*cmd_line);
	*cmd_line = new_line;
}	

int	len_var(char *cmd_line, int i)
{
	size_t	len;
	int		temp;

	temp = i;
	len = 0;
	while (ft_isalnum(cmd_line[temp]))
	{
		printf(":::: %c\n", cmd_line[temp]);
		len++;
		temp++;
	}
	printf("LEN %ld\n", len);
	return (len);
}

bool	is_expansible(char *cmd_line, int i)
{
	int		temp;
	int		s_quote;

	temp = i ;
	s_quote = 0;
	while (temp >= 0)
	{
		if (cmd_line[temp] == SINGLE_QUOTE)
		{
			s_quote++;
		}
		temp--;
	}
	if (s_quote % 2 == 0)
		return (true);
	return (false);
}


void	get_var_env(t_mini *mini, t_varenv *var)
{
	char	*var_name;
	//size_t	len;
	char	**env_start = mini->env;

	//len = ft_strlen(var->value);
	//printf("len en get_varen %ld\n", len);

	var_name = malloc (sizeof(char) * (var->len + 2));
	if (!var_name)
		return ;
	ft_strlcpy(var_name, var->value, var->len + 1);
	// printf("VAR_value %s\n", var->value);
	// printf("VAR_NAME %s\n", var_name);
	var_name[var->len] = '=';
	var_name[var->len + 1] = '\0';
	printf("VAR_NAME QUE TIENE QUE BUSCAR: %s\n", var_name);
	while (*mini->env != NULL)
	{
		if (!ft_strncmp(*mini->env, var_name, var->len))
		{
			var->var_expanded = (*mini->env + 1 + (var->len));
			break;
		}
		mini->env++;
	}
	mini->env = env_start; 
	free(var_name);
	//handle_error(ERR_ENVP);
	//printf("VAR_VALUE EN GET VAR: %s\n", var->value);
}

// int main(int ac, char **av, char **env)
// {
// 	if(ac != 2)
// 	{
// 		printf("incorrect arguments\n");
// 		return(1);
// 	}
// 	printf("%s\n", expand_varenv(av[1],env));
// 	return(0);

// }