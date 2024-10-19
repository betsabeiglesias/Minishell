/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/19 21:12:22 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
 
// if has_dollar => trocear

void	trim_toexpand(char *cmd_line, t_varenv *var, int *i, t_mini *mini)
{
	var->ant = ft_substr(cmd_line, 0, *i);
	printf("en trim la posición del pointer %d\n", *i);
	var->post = ft_substr(cmd_line, *i, len_var(var->pointer, i));
	printf("JUSTO ANTES DE GET VARENV\n");
	char *s;
	s = get_varenv(mini, var);
	printf("EXPANDE %s\n", s);
	printf("AAAAAA\n");

}

int	len_var(char *cmd_line, int *i)
{
	size_t	len;
	int		temp;

	temp = *i;
	len = 0;
	while(ft_isalnum(cmd_line[temp + 1]))
	{
		len++;
		temp += 1;
	}
	return(len);
}

bool	has_dollar(char *cmd_line, t_varenv *var, int *i)
{
	var->pointer = find_varposition(cmd_line, i);
	printf("en has dollar la posición del pointer %d\n", *i);
	if (var->pointer)
		return true;
	else
		return false;
}

bool	is_expansible(char *cmd_line, int *i)
{
	int 	temp;
	int		s_quote;
	
	temp = *i ;
	s_quote = 0;
	while(temp >= 0)
	{
		if(cmd_line[temp] == SINGLE_QUOTE)
		{
			s_quote++;
		}
		temp--;
	}
	if (s_quote % 2 == 0)
		return true ;
	return false;
}

char	*find_varposition(char *cmd_line, int *i)
{
	while(cmd_line[*i] != '\0')
	{
		if(cmd_line[*i] == '$' && is_expansible(cmd_line, i))
		{
			printf("en find_var la posición del pointer %d\n", *i);
			return (&cmd_line[*i]);
		}
		*i += 1;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{

	t_varenv *var = malloc(sizeof(t_varenv));
    if (var == NULL) {
        printf("Error al asignar memoria\n");
        return (1);
    }
	t_mini *mini = malloc(sizeof(t_mini));
    if (mini == NULL) {
        printf("Error al asignar memoria\n");
        return (1);
    }
	mini->env = get_my_env(envp, mini);
	int i = 0;
		
	if (argc < 2){
		printf("Incorrect arguments\n");
		return(1);
	}
	bool test;
	test = has_dollar(argv[1], var, &i);
	size_t len;
	len = len_var(argv[1], &i);
	// printf("la longitud de la variable %ld\n", len);
	// printf("el pointer esta en %s\n", var->pointer);
	if (!test)
		printf("no hay dollar expansible\n");
	else if (test)
	{
		printf("hay dollar expansible\n");
	}
	printf("justo antes de trime el pointer esta en %s\n", var->pointer);
	trim_toexpand(argv[1], var, &i, mini);
	printf("justo despues de trime el pointer esta en %s\n", var->pointer);
	//printf("VAR ANT %s\n", var->ant);
	//printf("VAR POST %s\n", var->post);
	free(var);
	return(0);
}



char	*get_varenv(t_mini *mini, t_varenv *var)
{
	char 	*var_name;
	size_t	len;

	len = ft_strlen(var->post);
	//printf("len en get_varen %ld\n", len);
	// // if(len == 0)
	// //	return(NULL);
	var_name = malloc (sizeof(char) * (len + 1));
	if(!var_name)
		return(NULL);
	ft_strlcpy(var_name, var->post + 1, len + 1);
	var_name[len - 1] = '=';
	var_name[len] = '\0';
	printf("PRINT VAR_NAME QUE TIENE QUE BUSCAR: %s\n", var_name);
	while(*mini->env != NULL)
	{

		if (!ft_strncmp(*mini->env, var_name, len))
		{
			free(var);
			return(*mini->env + (len));
		}
		mini->env++;
	}
	//printf("\n\n%s\n", var_name);
	free(var_name);
	//handle_error(ERR_ENVP);
	return (var->post);
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