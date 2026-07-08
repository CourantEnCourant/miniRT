NAME = libft.a

CC = cc
CFLAGS = -Wextra -Werror -Wall -g3
AR = ar rcs
RM = rm -f
INCLUDE = -I ../../include

SRC = ft_printf/ft_dprintf.c \
	  ft_printf/ft_printf.c \
	  ft_printf/ft_vdprintf.c \
	  ft_printf/parse_char.c \
	  ft_printf/parse_int.c \
	  ft_printf/parse_pointer.c \
	  ft_printf/parse_str.c \
	  ft_printf/parse_unsigned_hex.c \
	  ft_printf/parse_unsigned_int.c \
	  ft_printf/parser.c \
	  ft_atoi.c \
	  ft_bzero.c \
	  ft_calloc.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_isspace.c \
	  ft_itoa.c \
	  ft_lstadd_back.c \
	  ft_lstadd_front.c \
	  ft_lstclear.c \
	  ft_lstdelone.c \
	  ft_lstnew.c \
	  ft_lstsize.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_memset.c \
	  ft_putchar_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_putstr_fd.c \
	  ft_realloc.c \
	  ft_split.c \
	  ft_strchr.c \
	  ft_strcmp.c \
	  ft_strcspn.c \
	  ft_strdup.c \
	  ft_striteri.c \
	  ft_strjoin.c \
	  ft_strlcat.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strmapi.c \
	  ft_strncmp.c \
	  ft_strnstr.c \
	  ft_strrchr.c \
	  ft_strtrim.c \
	  ft_substr.c \
	  ft_tolower.c \
	  ft_toupper.c \
	  get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "Created $(NAME) with success"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "Removed all .o files in libft"

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
