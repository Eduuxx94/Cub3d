# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/17 19:20:47 by ede-alme          #+#    #+#              #
#    Updated: 2022/10/28 10:54:47 by ede-alme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_PATH = ./srcs/
SRC_PATH_PARSE = ./srcs/parse/
SRC_PATH_STR = ./srcs/ft_string/

INC_PATH = ./includes/

OBJ_PATH = ./objs/

SRC_NAME = 	main.c \

SRC_PARSE =	load_config.c \
			file.c \
			get_next_line.c \

SRC_STR =	ft_string.c \

SRC = $(SRC_NAME) $(SRC_PARSE) $(SRC_STR)

OBJ_NAME = $(SRC:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

MLX = includes/.mlx/libmlx_Linux.a

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(OBJ_PATH)%.o:$(SRC_PATH_PARSE)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -I/usr/include -Iincludes/.mlx -O3 -o  $@ -c $<

$(OBJ_PATH)%.o:$(SRC_PATH_STR)%.c
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