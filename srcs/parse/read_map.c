/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:25:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/26 22:26:45 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_get_sprite_path(char *line)
{
	(void)line;
	//falta retornar o path do sprite//
	return (NULL);
}

int	ft_file_config(t_file *file)
{
	char	*line;
	int		times;

	times = 0;
	while (++times <= 4)
	{
		line = get_next_line(file->fd);
		if (line && line[0] && line[0] == 'N' && line[1] && line[1] == 'O')
			file->_no = ft_get_sprite_path(line);
		if (line && line[0] && line[0] == 'S' && line[1] && line[1] == 'O')
			file->_no = ft_get_sprite_path(line);
		if (line && line[0] && line[0] == 'W' && line[1] && line[1] == 'E')
			file->_no = ft_get_sprite_path(line);
		if (line && line[0] && line[0] == 'E' && line[1] && line[1] == 'A')
			file->_no = ft_get_sprite_path(line);
		free(line);
	}
	if (!file->_ea || !file->_no || !file->_so || !file->_we)
		return (ft_free_sfile(file));
	return (0);
}

void	ft_file_init(t_file *file, char *file_path)
{
	file->_ea = NULL;
	file->_no = NULL;
	file->_so = NULL;
	file->_we = NULL;
	file->map = NULL;
	file->file_path = ft_strdup(file_path);
}

int	ft_file_check(char *file_path)
{
	int		i;
	char	*type;

	i = 0;
	type = ".cub";
	while (file_path[i] && (file_path[i] != '.' || file_path[i + 1] == '/'))
		i++;
	if ((!i || file_path[i - 1] == '/') && printf("Bad file name!\n"))
		exit(0);
	while (file_path[i] && *type && file_path[i] == *type++)
		i++;
	if (!*type && !file_path[i])
		return (0);
	else if (printf("Bad file type!\n"))
		exit(0);
	return (0);
}

int	ft_start_parse(char *file_path)
{
	t_file	file;

	file.fd = open(file_path, O_RDONLY);
	if (file.fd == -1 || ft_file_check(file_path))
		return (printf("Open file error!\n"));
	ft_file_init(&file, file_path);
	if (ft_file_config(&file))// && ft_file_map(&file)
		return (1);
	return (0);
}
