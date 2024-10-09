/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/09 13:01:59 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stddef.h>

typedef struct s_mini{
    char        **env;
	bool		oldpwd;
}               t_mini;

char *prompt(void);

#endif