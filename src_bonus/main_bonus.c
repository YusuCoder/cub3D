/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:52:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/10/02 15:59:20 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	(void)argv;
	// check_input(argc, argv);
	// check_map();
	// parse_map();
	init_data(&data);
	mlx_set_window_limit(data.mlx, MIN_WIDTH, MIN_HEIGHT, WIDTH, HEIGHT);
	mlx_resize_hook(data.mlx, &resize_hook, &data);
	mlx_close_hook(data.mlx, &close_hook, &data);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, simulation, &data);
	mlx_loop(data.mlx);
	free_exit(&data, EXIT_SUCCESS);
}
