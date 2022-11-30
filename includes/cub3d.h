/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:34:25 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 18:00:52 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>

# include ".mlx/mlx.h"
# include "parse.h"
# include "engine.h"

//main.c functions
int		ft_free_sfile(t_file *file);
int		main(int argc, char **argv);

#endif
