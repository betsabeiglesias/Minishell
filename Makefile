# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/11 10:06:38 by aolabarr          #+#    #+#              #
#    Updated: 2025/01/11 13:04:14 by aolabarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

NO_LINK = -c
CFLAGS = -Wall -Wextra -Werror -g3 -g
SFLAGS =  -fsanitize=address

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
LIBFT_DIR = ./lib/libft
LIBLST_DIR = ./lib/liblst
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(LIBLST_DIR) -llst -lreadline -g3

SRC =	main.c \
		environment.c \
		signals_1.c signals_2.c \
		handle_error.c \
		init_data.c \
		check_syntax_1.c check_syntax_2.c check_syntax_3.c check_utils.c \
		tokenization_1.c tokenization_2.c \
		free.c free_2.c \
		parse.c \
		expansion_1.c expansion_2.c expansion_3.c \
		command_list_1.c command_list_2.c \
		command_list_3.c command_list_aux.c \
		execution_1.c execution_2.c execution_3.c \
		builtin_export_1.c builtin_export_2.c \
		builtin_exit_2.c \
		builtin_env_exit_echo.c \
		builtin_unset.c builtin_pwd.c \
		builtin_cd_1.c builtin_cd_2.c builtin_cd_3.c \
		builtin_auxiliar.c \
				
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
	rm -f $(NAME) $(NAME_BET)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBLST_DIR)

clean:
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBLST_DIR)

re: fclean all

.PHONY: all fclean clean re lib

#.SILENT: