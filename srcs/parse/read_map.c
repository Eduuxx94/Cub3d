/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:25:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/27 22:33:02 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_file_config(t_file *file)
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

int	ft_file_check(char *file_path, char *type)
{
	char	*temp;
	int		i;
	int		fd;

	i = 0;
	temp = type;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (printf("Exception: File Open Error\t'%s'\n", strerror(errno)));
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

int	ft_start_parse(char *file_path)
{
	t_file	file;

	file.fd = open(file_path, O_RDONLY);
	if (ft_file_check(file_path, ".cub"))
		return (1);
	ft_file_init(&file, file_path);
	if (ft_file_config(&file))// && ft_file_map(&file)
		return (1);
	return (0);
}
