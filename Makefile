# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/26 20:23:17 by marcela           #+#    #+#              #
#    Updated: 2023/03/07 19:41:37 by mrichard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes #-fsanitize=thread
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
	./philo 3 310 200 100 1

.PHONY: all clean fclean re run

.SILENT: