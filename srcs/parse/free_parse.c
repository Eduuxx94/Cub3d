/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:19:15 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/26 22:24:26 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_sfile(t_file *file)
{
	if (file->map)
		free(file->map);
	if (file->_ea)
		free(file->_ea);
	if (file->_no)
		free(file->_no);
	if (file->_so)
		free(file->_so);
	if (file->_we)
		free(file->_we);
	if (file->file_path)
		free(file->file_path);
	printf("Limpou tudo\n");
	return (1);
}
