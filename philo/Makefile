# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 15:06:02 by aaghzal           #+#    #+#              #
#    Updated: 2025/02/03 11:26:13 by aaghzal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc
CFLAGS	= -Werror -Wall -Wextra

BUILD_DIR = build/

SRCS	= main.c output.c grim_reaper.c ft_strncmp.c \
		philosopher.c init.c exit.c time.c parsing.c
OBJS	= $(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
