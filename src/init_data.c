/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:25:42 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/27 16:36:29 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init(data->width, data->height, "cub3D", true);
	if (data->mlx == NULL)
		error_exit(data);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (data->img == NULL)
		error_exit(data);
}
