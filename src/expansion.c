/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/19 14:22:26 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"
 
// if has_dollar => trocear

void	trim_toexpand(char *cmd_line, t_varenv *var, int *i)
{
	var->ant = ft_substr(cmd_line, 0, *i);
	printf("en trim la posición del pointer %d\n", *i);
	var->post = ft_substr(cmd_line, *i, len_var(var->pointer, i));
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
	int		d_quote;
	
	temp = *i ;
	d_quote = 0;
	while(temp >= 0)
	{
		if(cmd_line[temp] == '\"')
		{
			d_quote++;
		}
		temp--;
	}
	if (d_quote % 2 == 0)
		return false;
	return true;
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

int main(int argc, char **argv)
{

	t_varenv *var = malloc(sizeof(t_varenv));
    if (var == NULL) {
        printf("Error al asignar memoria\n");
        return (1);
    }
	int i = 0;
		
	if (argc < 2){
		printf("Incorrect arguments\n");
		return(1);
	}
	bool test;
	test = has_dollar(argv[1], var, &i);
	size_t len;
	len = len_var(argv[1], &i);
	printf("la longitud de la variable %ld\n", len);
	printf("el pointer esta en %s\n", var->pointer);
	if (!test)
		printf("no hay dollar expansible\n");
	else if (test)
	{
		printf("hay dollar expansible\n");
	}
	printf("justo antes de trime el pointer esta en %s\n", var->pointer);
	trim_toexpand(argv[1], var, &i);
	printf("justo despues de trime el pointer esta en %s\n", var->pointer);
	printf("VAR ANT %s\n", var->ant);
	printf("VAR POST %s\n", var->post);
	free(var);
	return(0);
}



// char	*find_varenv(char *str, t_mini *mini)
// {
// 	char	*var;
// 	size_t	len;
	
// 	// if (!str || str[0] != '$')
// 	// 	return(NULL);
// 	len = ft_strlen(str) - 1;
// 	// if(len == 0)
// 	//	return(NULL);
// 	var = malloc (sizeof(char) * (len + 2));
// 	if(!var || !str)
// 		return(NULL);
// 	ft_strlcpy(var, str + 1, len + 1);
// 	var[len] = '=';
// 	var[len + 1] = '\0';
// 	while(*mini->env != NULL)
// 	{
// 		if (!ft_strncmp(*mini->env, var, len + 1))
// 		{
// 			free(var);
// 			return(*mini->env + (len + 1));
// 		}
// 		mini->env++;
// 	}
// 	free(var);
// 	//handle_error(ERR_ENVP);
// 	return (str);
// }

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