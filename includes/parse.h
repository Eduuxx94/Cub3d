/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:22:49 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/28 16:55:58 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <errno.h>
# include <string.h>

# include "get_next_line.h"
# include "ft_string.h"

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

//load_config.c functions
int		ft_start_parse(t_file *file, char *file_path);

//File.c functions
int		ft_file_init(t_file *file, char *file_path);
int		ft_file_check(char *file_path, char *type);
int		ft_file_load_tiles(t_file *file);

//load_colors.c functions
int		ft_check_file_colors(t_file *file);
int		ft_get_file_colors(t_rgb *rgb, char *str);
int		ft_color_line_export(char *str);

#endif