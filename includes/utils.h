/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:29:01 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 18:14:24 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_utils
{
	int		(*ft_strncmp)(const char *s1, const char *s2, size_t n);
	int		(*strisspace)(const char *str);
	size_t	(*strlen)(const char *s);
	char	*(*strtrim)(const char *str);
	char	*(*strdup)(const char *s);
	void	*(*memcpy)(void *dest, const void *src, size_t n);
	char	**(*matrixdup)(const char **matrix);
	int		(*matrixlen)(const char **matrix);
	void	(*matrixfree)(char **matrix);
	char	*(*get_next_line)(int fd);
}	t_utils;

typedef struct s_gnl {
	int		i;
	int		j;
	char	*temp;
	int		i_line;
	int		i_buffer;
}		t_gnl;

//main
t_utils	utils(void);

//Get_next_line.c Functions
char	*get_next_line(int fd);
char	*ft_get_buff(char *line, char *buffer, t_gnl var);

/*String functions*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strisspace(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(const char *str);
char	*ft_strdup(const char *s);

//Mem functions
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

//Matrix functions
char	**ft_matrixdup(const char **matrix);
int		ft_matrixlen(const char **matrix);
void	ft_matrixfree(char **matrix);

#endif
