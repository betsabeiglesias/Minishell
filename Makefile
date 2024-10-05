# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 12:55:45 by aolabarr          #+#    #+#              #
#    Updated: 2024/10/05 13:38:59 by aolabarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NO_LINK = -c
CFLAGS = -Wall -Wextra -Werror -g3
SFLAGS =  -fsanitize=address

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
LIBFT_DIR = ./lib/libft
LIBLST_DIR = ./lib/liblst
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(LIBLST_DIR) -llst -lreadline

SRC =	main_check.c \
		check.c \
				
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: lib $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(NO_LINK) $(CFLAGS) -I$(INC_DIR) $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

lib:
	make -C $(LIBFT_DIR)
	make -C $(LIBLST_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBLST_DIR)

clean:
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBLST_DIR)

re: fclean all

.PHONY: all fclean clean re lib sanitizer

#.SILENT: