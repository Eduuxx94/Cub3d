/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:29:01 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 12:12:26 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <stdlib.h>

typedef struct s_utils
{
	int		(*strisspace)(const char *str);
	size_t	(*strlen)(const char *s);
	char	*(*strtrim)(const char *str);
	char	*(*strdup)(const char *s);
	void	*(*memcpy)(void *dest, const void *src, size_t n);
	char	**(*matrixdup)(const char **matrix);
	size_t	(*matrixlen)(const char **matrix);
}	t_utils;

//main
t_utils	utils(void);

/*String functions*/
int		ft_strisspace(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(const char *str);
char	*ft_strdup(const char *s);

//Mem functions
void	*ft_memcpy(void *dest, const void *src, size_t n);

//Matrix functions
char	**ft_matrixdup(const char **matrix);
size_t	ft_matrixlen(const char **matrix);


#endif