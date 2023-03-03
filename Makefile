# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 20:23:17 by marcela           #+#    #+#              #
#    Updated: 2023/03/03 21:46:01 by mrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
RM = rm -rf
NAME = philo

SRCS = src/philo.c src/utils.c src/init.c src/threads.c src/actions.c src/exit_and_free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	echo "Building..."
	$(CC) $(CFLAGS) -pthread $(OBJS) -o philo
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: re
	./philo 5 800 200 200 2

.PHONY: all clean fclean re run

.SILENT: