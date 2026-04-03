NAME = cub3D
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g
MLX_LIB = minilibx-linux/libmlx_Linux.a
MLX_DIR = minilibx-linux
MLX_ARCHIVE = minilibx-linux.tgz
MLX_FLAGS = -L${MLX_DIR} -lmlx_Linux -lXext -lX11
LDLIBS = -lm
LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft -lft
# find . -name "*.c" | tr '\n' ' '
SRC_FILES = ./parse.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./ft_split_new.c
# SRC_FILES = ./main.c ./mlx_img_utils.c
OBJ_FILES = ${SRC_FILES:.c=.o}

all : ${NAME}

# ${NAME} : ${OBJ_FILES} ${MLX_LIB}
# 	${CC} ${C_FLAGS} -o ${NAME} ${OBJ_FILES} ${MLX_FLAGS} ${LDLIBS}

${NAME} : ${OBJ_FILES} ${LIBFT}
	${CC} ${C_FLAGS} -o ${NAME} ${OBJ_FILES} ${LIBFT_FLAGS}

${LIBFT} :
	make -C ./libft all

${MLX_LIB} : ${MLX_DIR}
	make -C ./${MLX_DIR} all

${MLX_DIR} :
	tar -xzf ${MLX_ARCHIVE};

# %.o : %.c ${MLX_LIB}
# 	${CC} ${C_FLAGS} -c $< -o $@

%.o : %.c
	${CC} ${C_FLAGS} -c $< -o $@

# clean :
# 	rm -rf ${OBJ_FILES}
# 	make -C ./$(MLX_DIR) clean

clean :
	make -C ./libft clean
	rm -rf ${OBJ_FILES}

# fclean : clean
# 	rm -f ${NAME}
# 	rm -rf ${MLX_DIR}

fclean : clean
	make -C ./libft fclean
	rm -f ${NAME}

re: fclean all
