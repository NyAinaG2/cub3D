NAME = cub3D

CC = clang

C_FLAGS = -Wall -Werror -Wextra -g

MLX_LIB = minilibx-linux/libmlx_Linux.a

MLX_DIR = minilibx-linux

MLX_ARCHIVE = minilibx-linux.tgz

MLX_FLAGS = -L${MLX_DIR} -lmlx_Linux -lXext -lX11

LDLIBS = -lm

LIBFT = libft/libft.a

LIBFT_FLAGS = -Llibft -lft

SRC_FILES = render/render.c \
			render/collision.c \
			render/init_render.c \
			render/key_handler.c \
			render/mlx_utils.c \
			render/move.c \
			render/textures.c\
			parse/parse.c \
			parse/parse_check_params.c\
			parse/parse_check_utils.c\
			parse/parse_exit_utils.c\
			parse/parse_get_next_map.c\
			parse/parse_map_close.c\
			parse/parse_map_height.c\
			parse/parse_utils.c\
			parse/parse_width.c\
			get_next_line/get_next_line.c\
			get_next_line/get_next_line_utils.c\
			dda/dda.c \
			main.c \

OBJ_FILES = ${SRC_FILES:.c=.o}

all : ${NAME}

${NAME} : ${LIBFT} ${MLX_LIB} ${OBJ_FILES} 
	${CC} ${C_FLAGS} -o ${NAME} ${OBJ_FILES} ${LIBFT_FLAGS} ${MLX_FLAGS} ${LDLIBS}

${LIBFT} :
	make -C ./libft all

${MLX_LIB} : ${MLX_DIR}
	make -C ./${MLX_DIR} all

%.o : %.c ${MLX_LIB} ${LIBFT}
	${CC} ${C_FLAGS} -c $< -o $@

clean :
	make -C ./libft clean
	rm -rf ${OBJ_FILES}
	make -C ./$(MLX_DIR) clean

fclean : clean
	make -C ./libft fclean
	rm -f ${NAME}

re: fclean all
