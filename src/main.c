/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:52:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/21 12:13:57 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	check_leaks(void)
// {
// 	system("leaks cub3d");
// }

int	main(int argc, char **argv)
{
	t_data	data;

	// atexit(check_leaks);
	(void)argc;
	if (parse(&data, argv) == 1)
		return (-1);
	else
	{
	init_data(&data);
	mlx_set_window_limit(data.mlx, MIN_WIDTH, MIN_HEIGHT, WIDTH, HEIGHT);
	mlx_resize_hook(data.mlx, &resize_hook, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, simulation, &data);
	// printf("\n\nhere\n\n");
	mlx_loop(data.mlx);
	free_exit(&data, EXIT_SUCCESS);
	}
	return (0);
}
