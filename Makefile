# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 09:32:14 by hlaaz             #+#    #+#              #
#    Updated: 2026/01/03 10:35:04 by hlaaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_atol.c  \
		ft_split.c \
		main.c \
		parsing.c \
		error_free.c \
		list_utils.c \
		push.c \
		swap.c \
		rrotate.c \
		rotate.c
OBJS	= $(SRCS:.c=.o)
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

NAME	= push_swap

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
