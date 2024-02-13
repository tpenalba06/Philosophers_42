# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 15:08:16 by npatron           #+#    #+#              #
#    Updated: 2024/02/13 20:21:36 by tpenalba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

SRC = main.c \
	  utils.c \
	  utils_2.c \
	  parsing.c \
	  init.c \
	  routine.c \
	  steve_jobs.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

.c.o:
	gcc $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
		gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all