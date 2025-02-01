CFLAGS := -Wall -Wextra -Werror
MLX_LIB := -lmlx -lXext -lX11 -lm

LIBFT := libft
LIBFTCHECK := libft/libft.a
SRC := solong.c hooks.c image.c map.c set_tiles.c moves.c animations.c\
	fence_corners.c fence_borders.c set_exit_flowers.c image_overwrite.c\
	image_utils.c map_check.c enemy.c enemy_moves.c animations_more.c
OBJ := $(SRC:.c=.o)

NAME := so_long
NAMEBONUS := so_long_bonus

all: ${NAME}

${NAME}: ${OBJ} ${LIBFTCHECK}
	@-cc -g $(CFLAGS) ${OBJ} ${MLX_LIB} -L $(LIBFT) -lft -o $(NAME)

# $(NAME): $(OBJ) ${LIBFTCHECK} #for WSL2
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L $(LIBFT) -lft -o $(NAME)

${OBJ}: ${SRC}
	@-cc -g -c ${CFLAGS} ${SRC}

${LIBFTCHECK}:
	@-${MAKE} -C ${LIBFT} bonus clean

b : bonus
bonus : $(NAMEBONUS)
$(NAMEBONUS) : ${OBJ} ${LIBFTCHECK}
	@-cc -g $(CFLAGS) ${OBJ} ${MLX_LIB} -L $(LIBFT) -lft -o $(NAMEBONUS)

c : clean
clean:
	@-rm -f ${OBJ}

f : fclean
fclean: clean
	@-${MAKE} -C ${LIBFT} fclean
	@-rm -f ${NAME} ${LIBFTCHECK} ${CLIENT} $(NAMEBONUS)

re: fclean all bonus

val:
	@valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./${NAME} novem.ber

fun:
	@funcheck ./${NAME} novem.ber

.PHONY: all bonus clean fclean re val fun
