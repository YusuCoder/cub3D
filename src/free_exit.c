/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:49:19 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/17 12:33:19 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_it(void **data)
{
	size_t	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	free_exit(t_data *data)
{
	mlx_close_window(data->mlx);
	if (data->img != NULL)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	if (data != NULL)
		data = NULL;
	exit(EXIT_SUCCESS);
}
