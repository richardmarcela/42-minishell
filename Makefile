# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riolivei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:49:40 by riolivei          #+#    #+#              #
#    Updated: 2023/04/14 20:25:46 by riolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -rf
LIBFT = ./libft/libft.a
VPATH = src src/parser src/utils src/parser/token src/parser/commands src/parser/env_list\
		src/bins src/builtins src/builtins/echo

UTILS = utils
TOKEN = create_token_list def_token_types token_utils
COMMANDS = create_commands_list
PARSER = parser
BINS = check_bins
BUILTINS = check_builtins
ECHO = echo echo2
ENV_LIST = env_list
MAIN = main

SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(TOKEN))\
		$(addsuffix .c, $(COMMANDS))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(ENV_LIST))\
		$(addsuffix .c, $(BINS))\
		$(addsuffix .c, $(BUILTINS))\
		$(addsuffix .c, $(ECHO))\
		$(addsuffix .c, $(MAIN))

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) --no-print-directory -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

run: re
	./minishell

PHONY: all clean fclean re run

.SILENT: