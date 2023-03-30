# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riolivei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:49:40 by riolivei          #+#    #+#              #
#    Updated: 2023/03/25 21:06:09 by riolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I./includes -fsanitize=address -g
RM = rm -rf
LIBFT = ./libft/libft.a
VPATH = src src/parser src/utils src/parser/token

UTILS = utils
TOKEN = create_token_list def_token_types
PARSER = parser pipe_split
MAIN = main

SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(TOKEN))\
		$(addsuffix .c, $(PARSER))\
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