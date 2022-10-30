/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:42:27 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 17:29:56 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_matrixfree(char **matrix)
{
	int	i;

	i = utils().matrixlen((const char **)matrix);
	while (--i >= 0)
	{
		if (matrix[i])
			free(matrix[i]);
	}
	if (matrix)
		free(matrix);
}

//Will allocate a new **array(char) and copy the entire contents of **matrix
char	**ft_matrixdup(const char **matrix)
{
	char	**array;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
		i++;
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	array[i] = NULL;
	while (--i >= 0)
		array[i] = ft_strdup(matrix[i]);
	return (array);
}

/*Will calculate the length of the **matrix*/
int	ft_matrixlen(const char **matrix)
{
	int	i;

	if (!matrix)
		return (0);
	i = 0;
	while (matrix[i])
		i++;
	return (i);
}
