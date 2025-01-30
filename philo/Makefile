CC := cc
CFLAGS := -Wall -Wextra -Werror
BUILD_DIR := build/
SRCS := actions.c azrael.c ft_atouc.c ft_atoull.c ft_intcmp.c ft_putchar_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_strncmp.c main.c min_max.c print_action.c \
		routine.c valid_input.c
OBJS := ${addprefix $(BUILD_DIR),$(SRCS:.c=.o)}
NAME := philo

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
