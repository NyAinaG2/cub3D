NAME = cub3D
CC = cc
C_FLAGS = -Wall -Werror -Wextra -g
MLX_LIB = minilibx-linux/libmlx_Linux.a
MLX_DIR = minilibx-linux
MLX_ARCHIVE = minilibx-linux.tgz
MLX_FLAGS = -L${MLX_DIR} -lmlx_Linux -lXext -lX11
SRC_FILES = ./main.c ./mlx_img_utils.c
OBJ_FILES = ${SRC_FILES:.c=.o}

all : ${NAME}

${NAME} : ${OBJ_FILES} ${MLX_LIB}
	${CC} ${C_FLAGS} -o ${NAME} ${OBJ_FILES} ${MLX_FLAGS}

${MLX_LIB} : ${MLX_DIR}
	make -C ./${MLX_DIR} all

${MLX_DIR} :
	tar -xzf ${MLX_ARCHIVE};

%.o : %.c ${MLX_LIB}
	${CC} ${C_FLAGS} -c $< -o $@

clean :
	rm -rf ${OBJ_FILES}
	make -C ./$(MLX_DIR) clean

fclean : clean
	rm -f ${NAME}
	rm -rf ${MLX_DIR}

re: fclean all
