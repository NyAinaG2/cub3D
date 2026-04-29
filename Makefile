NAME = cub3D

CC = clang

C_FLAGS = -Wall -Werror -Wextra

MLX_LIB = minilibx-linux/libmlx_Linux.a

MLX_DIR = minilibx-linux

MLX_ARCHIVE = minilibx-linux.tgz

MLX_FLAGS = -L${MLX_DIR} -lmlx_Linux -lXext -lX11

LDLIBS = -lm

LIBFT = libft/libft.a

LIBFT_FLAGS = -Llibft -lft

SRC_FILES = parse.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \

OBJ_FILES = ${SRC_FILES:.c=.o}

all : ${NAME}

${NAME} : ${OBJ_FILES} ${LIBFT} ${MLX_LIB}
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