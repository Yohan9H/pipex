# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 13:24:18 by yohurteb          #+#    #+#              #
#    Updated: 2024/06/27 14:42:59 by yohurteb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc -g

CFLAGS = -Wall -Werror -Wextra -I includes/

SRCS = \
	src/main.c \
	src/check_args.c \
	src/fork.c \
	src/fork_without_env.c \
	src/free.c \
	utils/ft_split.c \
	utils/ft_strdup.c \
	utils/ft_strlen.c \
	utils/ft_strncmp.c \
	utils/ft_strjoin.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re