/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:34:25 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/27 20:08:34 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>

# include ".mlx/mlx.h"

# include "get_next_line.h"
# include <errno.h>
# include <string.h>

typedef struct s_rgb
{
	char	red;
	char	green;
	char	blue;
	char	alpha;
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

//Parse functions
int		ft_start_parse(char *file_path);
int		ft_file_check(char *file_path, char *type);
void	ft_file_init(t_file *file, char *file_path);

//Free parse functions
int		ft_free_sfile(t_file *file);

//String functions
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *str);
size_t	ft_strlen(const char *s);

#endif