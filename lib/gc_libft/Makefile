NAME = gc_libft.a

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f

INCLUDE = -I ../../include
SRC = gc_basic.c \
	  gc_calloc.c \
	  gc_get_next_line.c \
	  gc_itoa.c \
	  gc_malloc.c \
	  gc_split.c \
	  gc_strdup.c \
	  gc_strjoin.c \
	  gc_strtrim.c \
	  gc_substr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in gc_libft"

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
