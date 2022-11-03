/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:57:48 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/03 20:51:40 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_get_buff(char *line, char *buffer, t_gnl var)
{
	var.i_line = 0;
	var.i_buffer = 0;
	var.temp = line;
	while (var.temp && var.temp[var.i_line])
		var.i_line++;
	while (buffer && buffer[var.i_buffer] && buffer[var.i_buffer++] != '\n')
		if (buffer && buffer[var.i_buffer] == '\n' && var.i_buffer++)
			break ;
	line = malloc(sizeof(char) * (var.i_line + var.i_buffer) + 1);
	if (!line)
		return (NULL);
	line[var.i_line + var.i_buffer] = 0;
	var.i_buffer = 0;
	var.i_line = 0;
	while (var.temp && var.temp[var.i_line] && ++var.i_line)
		line[var.i_line - 1] = var.temp[var.i_line - 1];
	free(var.temp);
	while (buffer && buffer[var.i_buffer] && var.i_buffer < BUFFER_SIZE)
	{
		line[var.i_line + var.i_buffer] = buffer[var.i_buffer];
		buffer[var.i_buffer] = '\0';
		if (line[var.i_line + var.i_buffer++] == '\n')
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[256][BUFFER_SIZE + 1];
	t_gnl		var;

	line = NULL;
	while (fd < 256 && fd != -1)
	{
		var.i = 0;
		var.j = 0;
		if (!buffer[fd][0] && (read(fd, buffer[fd], BUFFER_SIZE) <= 0))
			return (line);
		line = ft_get_buff(line, buffer[fd], var);
		while (line && var.i < BUFFER_SIZE && buffer[fd][var.i] == '\0')
			var.i++;
		while (var.i < BUFFER_SIZE)
		{
			buffer[fd][var.j++] = buffer[fd][var.i];
			buffer[fd][var.i++] = '\0';
		}
		var.i = 0;
		while (line && line[var.i])
			if (line[var.i++] == '\n')
				return (line);
	}
	return (line);
}
