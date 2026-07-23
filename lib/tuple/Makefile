NAME = tuple.a

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f

INCLUDE = -I ../../include
SRC = tuple.c \
	  tuple2.c \
	  tuple3.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in tuple"

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
