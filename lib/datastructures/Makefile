NAME = datastructures.a
TEST = test

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f

INCLUDE = -I ../../include

SRC = btree.c \
	  darray_functional.c \
	  darray_functional_2.c \
	  darray_io.c \
	  darray_io_2.c \
	  darray_ocf.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in datastructures"

fclean: clean
	@$(RM) $(NAME) $(TEST)
	@echo "Removed $(NAME) and $(TEST)"

test: $(NAME)
	@$(MAKE) -C ../libft
	@$(MAKE) -C ../gc_libft
	@$(CC) $(CFLAGS) $(INCLUDE) -x c test.norminette -x none $(NAME) ../gc_libft/gc_libft.a ../libft/libft.a -o $(TEST)
	@echo "Compiled ./${TEST}"

re: fclean all

.PHONY: all clean fclean re test
