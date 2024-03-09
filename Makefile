# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 12:36:50 by muhakose          #+#    #+#              #
#    Updated: 2024/03/09 13:31:43 by muhakose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOUR_DEFAULT = \033[0m
COLOUR_BLACK = \033[0;30m
COLOUR_RED = \033[0;31m
COLOUR_GREEN = \033[0;32m
COLOUR_YELLOW = \033[0;33m
COLOUR_BLUE = \033[0;34m
COLOUR_MAGENTA = \033[0;35m
COLOUR_CYAN = \033[0;36m
COLOUR_WHITE = \033[0;37m
COLOUR_BOLD = \033[1m
COLOUR_UNDERLINE = \033[4m
COLOUR_END = \033[0m

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./include/ -g -pthread
#CFLAGS +=-g3 -fsanitize=address -fsanitize=undefined

OBJ_DIR = obj
OBJ = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(wildcard src/*.c)) \

VALGRIND_ENABLED = 1

VALGRIND_CMD = valgrind
VALGRIND_OPTS = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

TARGET = philo

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)


run_valgrind: $(TARGET)
	@echo "Running $(TARGET) with Valgrind..."
	$(VALGRIND_CMD) $(VALGRIND_OPTS) ./$(TARGET) 3 600 350 400 5

NAME = philo

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	echo "$(COLOUR_YELLOW)Philo compiled successfully!$(COLOUR_END)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	echo "$(COLOUR_BLUE)$(COLOUR_UNDERLINE)Philo cleaned successfully!$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re

valgrind:
	$(MAKE) run_valgrind

.PHONY: show_errors
show_errors:
	$(VALGRIND_CMD) $(VALGRIND_OPTS) --log-file=valgrind_errors.txt ./$(TARGET)
	cat valgrind_errors.txt
	rm -f valgrind_errors.txt
