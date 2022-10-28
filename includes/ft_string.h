/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:29:01 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/28 10:51:53 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <string.h>
# include <stdlib.h>

//String functions
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *str);
size_t	ft_strlen(const char *s);

#endif