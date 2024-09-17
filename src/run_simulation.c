/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:21:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/09/17 12:48:06 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	radian(int degree)
{
	double	result;

	result = degree * (M_PI / 180);
	return (result);
}

// void	check_horizontal_intersection()
// {

// }

// void	ray_casting(t_data *data)
// {
// 	check_horizontal_intersection();
// 	check_verticalal_intersection();
// }

void	run_simulation(t_data *data)
{
	// ray_casting(data);
	mlx_loop(data->mlx);
}
