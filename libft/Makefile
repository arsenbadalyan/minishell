# Variables
NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
EXECUTABLE = result
RM = rm -rf
AR = ar rc
RUN = ranlib
LIBS   = -I ../includes/

# Source Files
SRC = $(wildcard *.c)

# Object Files
OBJ = $(patsubst %.c, %.o, $(SRC))

# Colors
RESET  = \033[0m
GREEN  = \033[32m
BLUE   = \033[34m


# Rules
all: $(NAME)
	@echo > /dev/null

$(NAME): Makefile $(OBJ)
	@$(AR) $@ $(OBJ)
	@$(RUN) $@

%.o: %.c ../includes/libft.h
	@echo "${BLUE}Compiling $<${RESET}"
	@$(CC) $(FLAGS) $(LIBS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re