# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riolivei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 10:49:40 by riolivei          #+#    #+#              #
#    Updated: 2023/02/28 21:44:22 by riolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBFT = ./libft/libft.a

SRCS = src/main.c src/output.c src/processing.c src/utils.c \
	src/directory.c src/split.c src/print.c src/quotes.c

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