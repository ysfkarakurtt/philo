# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 14:09:32 by ykarakur          #+#    #+#              #
#    Updated: 2024/09/05 11:52:51 by ykarakur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = philo.c \
		input_check.c \
		actions.c \
		time_planning.c \
		philo_create.c \
		threads.c \
		mutexes.c 
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "**philo created**\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(NAME)
	@printf "**object files deleted***\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "**executable name deleted**\n"

re: fclean all

.PHONY: all clean fclean re
