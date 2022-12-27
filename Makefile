# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 19:20:47 by ede-alme          #+#    #+#              #
#    Updated: 2022/12/26 23:17:25 by ede-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC_PATH = ./srcs/
SRC_PATH_PARSE = ./srcs/parse/
SRC_PATH_UTILS = ./srcs/utils/
SRC_PATH_ENGINE = ./srcs/engine/


INC_PATH = ./includes/

OBJ_PATH = ./objs/

SRC_NAME = 	main.c \

SRC_PARSE =	parse.c \
			parse_utils.c \
			file.c \
			colors.c \
			map.c \

SRC_UTILS =	utils.c \
			get_next_line.c \
			string.c \
			mem.c \
			matrix.c \

SRC_ENGINE = engine.c \
			engine_utils.c \
			events.c \
			raycast1.c \
			raycast2.c \
			raycast_utils.c \
			anim.c \
			sound.c \
			minimap1.c \
			minimap2.c \
			loading.c \

SRC = $(SRC_NAME) $(SRC_PARSE) $(SRC_UTILS) $(SRC_ENGINE)

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLX = includes/.mlx/libmlx_Linux.a

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(OBJ_PATH)%.o:$(SRC_PATH_PARSE)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(OBJ_PATH)%.o:$(SRC_PATH_UTILS)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(OBJ_PATH)%.o:$(SRC_PATH_ENGINE)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_PATH) -o $@ -Lincludes/.mlx -lmlx_Linux -L/usr/lib -Iincludes/.mlx -lXext -lX11 -lm -lz

$(MLX):
	@make -s -C includes/.mlx/

all: $(NAME)

clean:
	@make clean -C includes/.mlx/
	rm -rf $(OBJ_PATH)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re