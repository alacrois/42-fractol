NAME = fractol

SRCS =	main.c \
		hook_functions.c \
		display.c \
		complex_operations.c \
		newton.c \
		mandelbrot.c \
		mega_mandelbrot.c \
		tricorn.c \
		burning_ship.c \
		julia.c \
		julia_brain.c \
		julia_wtf.c \
		snowflake_1.c \
		snowflake_2.c \
		snowflake_3.c \
		misc_1.c \
		misc_2.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -Ofast

CC = gcc $(FLAGS)

all : $(NAME)

make_libft :
	make -C libft

$(NAME) : make_libft $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft -lmlx -framework OpenGL -framework AppKit

clean :
	rm -f $(OBJS) *~ *#

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re