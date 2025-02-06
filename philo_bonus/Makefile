# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 17:22:56 by aaghzal           #+#    #+#              #
#    Updated: 2025/02/06 12:31:07 by aaghzal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

CC		= cc
CFLAGS	= -Werror -Wall -Wextra

BUILD_DIR = build/

SRCS	= main_bonus.c output_bonus.c parsing_bonus.c \
		grim_reaper_bonus.c philosopher_utils_bonus.c \
		time_bonus.c ipc_bonus.c philosopher_bonus.c \
		utils_bonus.c cleanup_bonus.c exit_bonus.c \
		init_bonus.c ft_strncmp_bonus.c
OBJS	= $(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o: $(SRC_PATH)%.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

bonus: all

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean bonus
