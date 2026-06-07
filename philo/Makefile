# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/07 19:22:45 by admin             #+#    #+#              #
#    Updated: 2026/06/07 21:01:09 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -g3 -O0
VPATH = src:../test
NAME = philo
TEST_NAME = test_philo

# Directories
INCLUDES = -Iincludes
OBJ_DIR = obj

# Sources and Objects
SRC = main.c manip_args.c utils.c
TEST_SRC = test_main.c test_args.c
	
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBFT_ARCHIVE = $(LIBFT_DIR)/libft.a

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
