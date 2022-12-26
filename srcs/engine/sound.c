/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 13:25:23 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/26 14:41:37 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <sys/wait.h>

int	play_sound(char *cmd)
{
	int	sound;

	if (!fork())
	{
		sound = system(cmd);
		exit(0);
		(void)sound;
	}
	return (1);
}
