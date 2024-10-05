# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 13:48:44 by aolabarr          #+#    #+#              #
#    Updated: 2024/04/27 13:52:59 by aolabarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
OBJ_CREATE = -c
CFLAGS = -Wall -Wextra -Werror

SRC = ftps_lstnew.c ftps_lstadd_front.c ftps_lstsize.c \
	  ftps_lstlast.c ftps_lstadd_back.c ftps_lstdelone.c \
	  ftps_lstclear.c

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
