# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 00:35:59 by tkondo            #+#    #+#              #
#    Updated: 2024/05/16 03:12:25 by tkondo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

# Source and object files
S_ALL =\
	get_next_line.c\
	get_next_line_utils.c

S_BONUS =\
	get_next_line_bonus.c\
	get_next_line_utils_bonus.c

O_ALL = $(S_ALL:%.c=%.o)
O_BONUS = $(S_BONUS:%.c=%.o)

ifdef BONUS
O_ALL = $(O_BONUS)
endif

# Name of the library
NAME = get_next_line.a

# Default target
all: $(NAME)

# Rule for creating the library
$(NAME): $(O_ALL)
	ar rcs $(NAME) $(O_ALL)

# Rule for bonus target
bonus:
	@make BONUS=1
# Rule for creating extra

# Rule for compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Rule for cleaning object files
clean:
	rm -f $(O_ALL) $(O_BONUS)

# Rule for full clean
fclean: clean
	rm -f $(NAME)

# Rule for re-making
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re

