CFLAGS := -Wall -Wextra -Werror

LIBFT := libft
LIBFTCHECK := libcheck/libft.a
 
SRC := solong.c hooks.c image.c map.c fences.c
OBJ := $(SRC:.c=.o)
NAME := solong

all: ${NAME} clean
	./$(NAME)

${NAME}: ${OBJ} ${LIBFTCHECK}
	cc -g $(CFLAGS) ${OBJ} -lmlx -lXext -lX11 -lm -lz -L $(LIBFT) -lft -o $(NAME)

# $(NAME): $(OBJ) ${LIBFTCHECK} #for WSL2
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L $(LIBFT) -lft -o $(NAME)

${OBJ}: ${SRC}
	cc -g -c ${CFLAGS} ${SRC}

${LIBFTCHECK}:
	@- ${MAKE} -C ${LIBFT} bonus clean

b : bonus
bonus :

c : clean
clean:
	@- rm -f ${OBJ} checker.o push_swap.o

f : fclean
fclean: clean
	@ ${MAKE} -C ${LIBFT} fclean
	rm -f ${NAME} ${LIBFTCHECK} ${CLIENT}

re: fclean all bonus

val: all
	@valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./${NAME}

fun: all
	@funcheck ${NAME}

.PHONY: all bonus clean fclean re val fun
