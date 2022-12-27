/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:22:49 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/26 23:05:21 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <errno.h>
# include <string.h>

# include "utils.h"

typedef struct s_rgb
{
	int	rgb;
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_rgb;

typedef struct s_file
{
	char	**id;
	int		fd;
	char	*file_path;
	char	*_no;
	char	*_so;
	char	*_we;
	char	*_ea;
	t_rgb	floor;
	t_rgb	ceilling;
	char	**map;
}	t_file;

//parse.c functions
int		ft_get_map_alloc(t_file *file, int size);
int		ft_file_map(t_file *file);
int		ft_start_parse(t_file *file, char *file_path);

//File.c functions
int		ft_check_tile(char **tile, char *line, char *cardinal);
int		ft_file_load_tiles(t_file *file);
int		ft_file_check(char *file_path, char *type);
int		ft_file_init(t_file *file, char *file_path);

//colors.c functions
int		rgb(int r, int g, int b);
int		ft_color_line_export(char *str);
int		ft_get_file_colors(t_rgb *rgb, char *str);
int		ft_check_file_colors(t_file *file);

//map.c functions
int		ft_player_range(char **map);
int		ft_check_map(char **map, int x, int y);
int		get_map_pos(char **map, char pos);
int		ft_map_player_count(char **map);

//parse_utils.c functions
int		is_player(char c);
int		is_valid_map_obj(char c);

#endif