# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varandri <varandri@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/30 16:45:00 by varandri          #+#    #+#              #
#    Updated: 2026/08/30 19:33:59 by varandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -pthread

SRC = main.c helpers.c utils_config.c utils_coder.c utils_cleaner.c \
		utils_dongle_0.c utils_dongle_1.c utils_queue_0.c utils_queue_1.c \
		utils_monitor.c utils_simulation_0.c utils_simulation_1.c \
		utils_verifier.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
.PHONY : all clean fclean re