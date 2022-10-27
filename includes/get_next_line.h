/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:58:15 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/26 20:19:58 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_gnl {
	int		i;
	int		j;
	char	*temp;
	int		i_line;
	int		i_buffer;
}		t_gnl;

//Main Function
char	*get_next_line(int fd);

//Utils Functions
char	*ft_get_buff(char *line, char *buffer, t_gnl var);

#endif