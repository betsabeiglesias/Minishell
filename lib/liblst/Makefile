# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/17 15:08:51 by aolabarr          #+#    #+#              #
#    Updated: 2024/11/03 13:24:04 by aolabarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liblst.a

CC = cc
NO_LINK = -c
CFLAGS = -Wall -Wextra -Werror

SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	  ft_lstclear.c

OBJ_DIR = ./obj
SRC_DIR = ./src
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

$(NAME): $(OBJ_DIR) $(OBJ)
	ar -cr $(NAME) $(OBJ)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(NO_LINK) $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir obj

fclean: clean
	rm -f $(NAME) *.out

clean:
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	rm -f *.o

re: fclean all 

.PHONY: all fclean clean re

#.SILENT:
