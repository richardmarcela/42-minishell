# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:49:40 by riolivei          #+#    #+#              #
#    Updated: 2023/07/18 16:54:17 by mrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -I./includes #-fsanitize=address
RM = rm -rf
LIBFT = ./libft/libft.a
VPATH = src src/parser src/utils src/parser/token src/parser/commands src/parser/env_list\
		src/bins src/builtins src/builtins/echo	src/builtins/export src/parser/env src/pipe\
		src/redir

UTILS = utils utils2
TOKEN = create_token_list def_token_types token_utils
COMMANDS = create_commands_list
PARSER = parser parser_utils parser_utils2 parser_utils3
ENV = create_env_list
BINS = check_bins check_bins_utils signal_handler
BUILTINS = check_builtins env cd unset exit
ECHO = echo
EXPORT = export
PIPE = pipe
REDIR = redir
MAIN = main free_structs

SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(TOKEN))\
		$(addsuffix .c, $(COMMANDS))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(ENV))\
		$(addsuffix .c, $(BINS))\
		$(addsuffix .c, $(BUILTINS))\
		$(addsuffix .c, $(ECHO))\
		$(addsuffix .c, $(EXPORT))\
		$(addsuffix .c, $(PIPE))\
		$(addsuffix .c, $(REDIR))\
		$(addsuffix .c, $(MAIN))\

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@printf "\n"
	@echo $(G)"       _     _     _       _ _ "$(X)
	@echo $(G)" _____|_|___|_|___| |_ ___| | |"$(X)
	@echo $(G)"|     | |   | |_ -|   | -_| | |"$(X)
	@echo $(G)"|_|_|_|_|_|_|_|___|_|_|___|_|_|"$(X)
	@printf "\n\n"

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME) $(LIBFT)

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

run: re
	./minishell

PHONY: all clean fclean re run

.SILENT: