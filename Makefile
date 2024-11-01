# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 12:55:45 by aolabarr          #+#    #+#              #
#    Updated: 2024/11/01 12:57:40 by aolabarr         ###   ########.fr        #
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
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(LIBLST_DIR) -llst -lreadline

SRC =	main_parse.c \
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
SRC_BET =  environment.c \
			expansion.c expansion_prep.c \
			#builtin_env.c\
			#handle_error.c \
			#builtin_cd.c builtin_pwd.c builtin_echo.c main_prompt.c\
			#prompt.c 
				
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