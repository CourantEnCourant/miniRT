NAME = vector.a

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f

INCLUDE = -I ../../include
SRC = vector.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in vector"

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
