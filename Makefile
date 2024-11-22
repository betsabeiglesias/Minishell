# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/11/23 14:43:43 by beiglesi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

# para borrar
NAME_BET = mini_bet

NO_LINK = -c
CFLAGS = -Wall -Wextra -Werror -g3
SFLAGS =  -fsanitize=address

SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc
LIBFT_DIR = ./lib/libft
LIBLST_DIR = ./lib/liblst
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(LIBLST_DIR) -llst -lreadline -g3

SRC =	main.c \
		environment.c \
		signals.c \
		handle_error.c \
		init_data.c \
		check_syntax_1.c \
		check_syntax_2.c \
		check_syntax_3.c \
		check_utils.c \
		tokenization_1.c \
		tokenization_2.c \
		free.c \
		parse.c \
		expansion_1.c \
		expansion_2.c \
		command_list_1.c \
		command_list_2.c \
		command_list_aux.c \
		execution_1.c \
		aux.c \

SRC_ARITZ =	main_parse.c \
			check_syntax_1.c \
			check_syntax_2.c \
			check_utils.c \
			handle_error.c \
			tokenization_1.c \
			tokenization_2.c \
			init_data.c \
			free.c \
			parse.c \

# para borrar
SRC_BET = main_bet.c \
		environment.c \
		signals.c \
		handle_error.c \
		init_data.c \
		check_syntax_1.c \
		check_syntax_2.c \
		check_syntax_3.c \
		check_utils.c \
		tokenization_1.c \
		tokenization_2.c \
		free.c \
		parse.c \
		expansion_1.c \
		expansion_2.c \
		command_list_1.c \
		command_list_2.c \
		command_list_aux.c \
		aux.c \
		builtin_export.c \
		builtin_env_exit_echo.c \
		builtin_unset.c \
		builtin_pwd.c \
		builtin_cd_1.c \
		builtin_cd_2.c \
		builtin_auxiliar.c \
				
				
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# para borrar
OBJS_BET = $(addprefix $(OBJ_DIR)/,$(SRC_BET:.c=.o))

all: lib $(OBJ_DIR) $(NAME)

# para borrar
bet: lib $(OBJ_DIR) $(NAME_BET)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# para borrar
$(NAME_BET): $(OBJS_BET)
	$(CC) $(CFLAGS) $(OBJS_BET) $(LDFLAGS) -o $(NAME_BET) 

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

.PHONY: all fclean clean re lib sanitizer

#.SILENT: