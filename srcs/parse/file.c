/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:18:47 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/28 18:37:36 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_file_load_tiles(t_file *file)
{
	char	*ln;
	char	*temp;

	while (!file->_ea || !file->_no || !file->_so || !file->_we)
	{
		temp = get_next_line(file->fd);
		if (temp == NULL)
			break ;
		ln = ft_strtrim(temp);
		free(temp);
		if (ft_strlen(ln) > 3 && ln[0] == 'N' && ln[1] == 'O' && ln[2] == ' ')
			file->_ea = ft_strtrim(ln + 2);
		if (ft_strlen(ln) > 3 && ln[0] == 'S' && ln[1] == 'O' && ln[2] == ' ')
			file->_no = ft_strtrim(ln + 2);
		if (ft_strlen(ln) > 3 && ln[0] == 'W' && ln[1] == 'E' && ln[2] == ' ')
			file->_so = ft_strtrim(ln + 2);
		if (ft_strlen(ln) > 3 && ln[0] == 'E' && ln[1] == 'A' && ln[2] == ' ')
			file->_we = ft_strtrim(ln + 2);
		free(ln);
	}
	if (ft_file_check(file->_ea, ".xpm") || ft_file_check(file->_no, ".xpm") || \
		ft_file_check(file->_so, ".xpm") || ft_file_check(file->_we, ".xpm"))
		return (1);
	return (0);
}

int	ft_file_check(char *file_path, char *type)
{
	char	*temp;
	int		i;
	int		fd;

	i = 0;
	temp = type;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (printf("Exception:\t%s:\t'%s'\n", file_path, strerror(errno)));
	while (file_path[i] && (file_path[i] != '.' || file_path[i + 1] == '/'))
		i++;
	if ((!i || file_path[i - 1] == '/') && !close(fd))
		return (printf("Bad file name!\n"));
	while (file_path[i] && *type && file_path[i] == *type++)
		i++;
	if (!*type && !file_path[i])
		return (close(fd));
	else if (!close(fd))
		printf("Bad file type!\tEXPECTED: '*%s'\n", temp);
	return (1);
}

int	ft_file_init(t_file *file, char *file_path)
{
	file->ceilling.red = -1;
	file->ceilling.green = -1;
	file->ceilling.blue = -1;
	file->floor.red = -1;
	file->floor.green = -1;
	file->floor.blue = -1;
	file->file_path = ft_strtrim(file_path);
	if (ft_file_check(file->file_path, ".cub"))
		return (1);
	file->fd = open(file->file_path, O_RDONLY);
	return (0);
}
