NAME = cub3D
CC = cc
C_FLAGS = -Wall -Werror -Wextra
MLX_LIB = minilibx-linux/libmlx_Linux.a
MLX_DIR = minilibx-linux
MLX_ARCHIVE = minilibx-linux.tgz
MLX_FLAGS = -L${MLX_DIR} -lmlx_Linux -lXext -lX11
LDLIBS = -lm
LIBFT = libft/libft.a
LIBFT_FLAGS = -Llibft -lft
# find . -name "*.c" | tr '\n' ' '
SRC_FILES = ./parse.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c ./libft/ft_atoi.c ./libft/ft_bzero.c ./libft/ft_calloc.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_lstadd_back_bonus.c ./libft/ft_lstadd_front_bonus.c ./libft/ft_lstclear_bonus.c ./libft/ft_lstdelone_bonus.c ./libft/ft_lstiter_bonus.c ./libft/ft_lstlast_bonus.c ./libft/ft_lstmap_bonus.c ./libft/ft_lstnew_bonus.c ./libft/ft_lstsize_bonus.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c ./libft/ft_split.c ./libft/ft_strchr.c ./libft/ft_strdup.c ./libft/ft_striteri.c ./libft/ft_strjoin.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c ./libft/ft_strncmp.c ./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtrim.c ./libft/ft_substr.c ./libft/ft_tolower.c ./libft/ft_toupper.c ./ft_split_new.c
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
