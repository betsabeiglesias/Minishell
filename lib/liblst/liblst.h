/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:40:19 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/31 18:57:27 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLST_H
# define LIBLST_H

# include <stdlib.h>

typedef enum	e_type
{
    CMD,
	RDS_IN,
	RDS_OUT,
	RDD_IN,
	RDD_OUT,
	PIPE,
	FILENAME,
	STR,
	EIT_CODE,
	NO_TYPE
}				t_type;

typedef struct s_token
{
	t_type		type;
	char		*content;
}			t_token;

typedef struct s_list
{
	t_token			token;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list	*ft_lstnew(char *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
#endif