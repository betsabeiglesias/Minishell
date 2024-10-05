# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 13:48:44 by aolabarr          #+#    #+#              #
#    Updated: 2024/10/05 17:42:03 by aolabarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
OBJ_CREATE = -c
CFLAGS = -Wall -Wextra -Werror

SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	  ft_lstclear.c

OBJS = $(SRC:.c=.o)
NAME = liblst.a

$(NAME): $(OBJS)
	ar -cr $(NAME) $(OBJS)

all: $(NAME)

%.o: %.c
	$(CC) $(OBJ_CREATE) $(CFLAGS) $< -o $@

fclean: clean
	rm -f $(NAME) *.out

clean:
	rm -f *.o

re: fclean all

.PHONY: all fclean clean re


#.SILENT:
