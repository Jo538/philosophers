# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/07 19:22:45 by admin             #+#    #+#              #
#    Updated: 2026/06/18 15:17:45 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
ADDITIONAL_FLAGS = -lpthread
VPATH = src:../test
NAME = philo
TEST_NAME = test_philo

# Directories
INCLUDES = -Iincludes
OBJ_DIR = obj

# Sources and Objects
SRC = main.c manip_args.c utils.c setup.c actions.c routine.c utils_bis.c \
		forks.c launch.c exit_checks_monitor.c exit_checks_routine.c
TEST_SRC = test_main.c test_args.c test_setup.c test_exit.c
	
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Default rule
all: $(NAME)

# Linking
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(NAME)

# Object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Phony targets declaration
.PHONY: all clean fclean re test

# Clean project's object files
clean:
	@rm -rf $(OBJ_DIR)

# Clean minishell executable and clean libraries
fclean: clean
	@rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all

# Create test binary
test: $(TEST_SRC) $(SRC)
	$(CC)  -DTESTING  $(INCLUDES) $(filter-out src/main.c, $^) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(TEST_NAME)
