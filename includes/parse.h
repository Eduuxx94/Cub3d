/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:22:49 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 18:06:21 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <errno.h>
# include <string.h>

# include "get_next_line.h"
# include "utils.h"

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_rgb;

typedef struct s_file
{
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
int		ft_file_map(t_file *file);
int		ft_start_parse(t_file *file, char *file_path);

//File.c functions
int		ft_file_init(t_file *file, char *file_path);
int		ft_file_check(char *file_path, char *type);
int		ft_file_load_tiles(t_file *file);

//colors.c functions
int		ft_check_file_colors(t_file *file);
int		ft_get_file_colors(t_rgb *rgb, char *str);
int		ft_color_line_export(char *str);

//map.c functions
int		ft_check_map(char **map, int x, int y);
int		get_map_pos(char **map, char pos);
int		is_player(char c);
int		is_valid_map_obj(char c);
int		ft_map_player_count(char **map);

#endif