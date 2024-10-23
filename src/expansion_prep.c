/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/23 12:21:42 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	trim_to_expand(char *cmd_line, t_varenv *var, int *i)
{
	size_t	len;

	len = len_var(var->pointer) + 1;
	var->ant = ft_substr(cmd_line, 0, *i);
	var->value = ft_substr(cmd_line, *i, len);
	*i += len;
	var->post = ft_substr(cmd_line, *i, (ft_strlen(cmd_line) - *i));
	// printf("var_post es: %s\n",var->post);
	// printf("var_ant es: %s\n",var->ant);
	// printf("VAR_VALUE es: %s\n",var->value);
}

char	*expanded_cmd_line(t_varenv *var, t_mini *mini)
{
	char	*new_cmd_line;
	char	*temp;
	char	*exp;

	exp = get_var_env(mini, var);
	// printf("EXPANDE %s\n", exp);
	// printf("var_post es: %s\n",var->post);
	// printf("var_ant es: %s\n",var->ant);
	// printf("VAR_VALUE es: %s\n",var->value);
	temp = ft_strjoin(var->ant, exp);
	free(var->value);
	free(var->ant);
	new_cmd_line = ft_strjoin(temp, var->post);
	free(var->post);
	return (new_cmd_line);
}

int	len_var(char *cmd_line)
{
	size_t	len;
	int		temp;

	temp = 1;
	len = 0;
	while (ft_isalnum(cmd_line[temp]))
	{
		len++;
		temp++;
	}
	return (len);
}

bool	has_dollar(char *cmd_line, t_varenv *var, int *i)
{
	var->pointer = find_value_position(cmd_line, i);
	if (var->pointer)
		return (true);
	else
		return (false);
}

bool	is_expansible(char *cmd_line, int *i)
{
	int		temp;
	int		s_quote;

	temp = *i ;
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

char	*find_value_position(char *cmd_line, int *i)
{
	while (cmd_line[*i] != '\0')
	{
		if (cmd_line[*i] == '$' && is_expansible(cmd_line, i))
			return (&cmd_line[*i]);
		*i += 1;
	}
	return (NULL);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_varenv *var = malloc(sizeof(t_varenv));
//     if (var == NULL) {
//         printf("Error al asignar memoria\n");
//         return (1);
//     }
// 	t_mini *mini = malloc(sizeof(t_mini));
//     if (mini == NULL) {
//         printf("Error al asignar memoria\n");
//         return (1);
//     }
// 	mini->env = get_my_env(envp, mini);
// 	int i = 0;
// 	if (argc < 2){
// 		printf("Incorrect arguments\n");
// 		return(1);
// 	}
// 	bool test;
// 	test = has_dollar(argv[1], var, &i);
// 	if (!test)
// 		printf("no hay dollar expansible\n");
// 	else if (test)
// 	{
// 		printf("hay dollar expansible\n");
// 	}
// 	trim_to_expand(argv[1], var, &i);
// 	char *result;
// 	result = expanded_cmd_line(var, mini);
// 	printf("RESULTADO: %s\n", result);
// 	free(var);
// 	return(0);
// }

char	*get_var_env(t_mini *mini, t_varenv *var)
{
	char	*var_name;
	size_t	len;

	len = ft_strlen(var->value);
	//printf("len en get_varen %ld\n", len);
	// // if(len == 0)
	// //	return(NULL);
	var_name = malloc (sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, var->value + 1, len + 1);
	var_name[len - 1] = '=';
	var_name[len] = '\0';
	// printf("VAR_NAME QUE TIENE QUE BUSCAR:%s\n", var_name);
	while (*mini->env != NULL)
	{
		if (!ft_strncmp(*mini->env, var_name, len))
		{
			free(var_name);
			return (*mini->env + (len));
		}
		mini->env++;
	}
	free(var_name);
	//handle_error(ERR_ENVP);
	//printf("VAR_VALUE EN GET VAR: %s\n", var->value);
	return (var->value);
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