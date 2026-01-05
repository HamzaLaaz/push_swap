# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaaz <hlaaz@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 09:32:14 by hlaaz             #+#    #+#              #
#    Updated: 2026/01/05 12:11:36 by hlaaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_atol.c  \
			ft_split.c \
			main.c \
			parsing.c \
			error_free.c \
			list_utils.c \
			push.c \
			swap.c \
			rrotate.c \
			rotate.c \
			sort.c \
			sort_utils.c \
			chunk_sort.c

OBJS		= $(SRCS:.c=.o)

NAME		= push_swap

BONUS_SRCS	= checker_bonus.c \
			get_next_line.c\
			get_next_line_utils.c \
			push.c \
			swap.c \
			rrotate.c \
			rotate.c

OBJSBNS		= $(BONUS_SRCs:.c=.o)

NAME_BONUS	= checker

CC			= cc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJSBNS)
	$(CC) $(CFLAGS) $(OBJSBNS) -o $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJSBNS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean bonus re
