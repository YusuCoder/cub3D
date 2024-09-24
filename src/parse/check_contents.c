/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_contents.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:51:43 by ryusupov          #+#    #+#             */
/*   Updated: 2024/09/24 17:43:54 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	map_content_check(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	data->player.c = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			while (data->map_info.map[i][j] == ' ' || data->map_info.map[i][j] == '\t' || data->map_info.map[i][j] == '\v')
				j++;
			if (!(ft_strchr("10NSEW", map[i][j])))
				exit(EXIT_FAILURE);
			if (ft_strchr("NSEW", map[i][j]) && data->player.c != '0')
				exit(EXIT_FAILURE);
			if (ft_strchr("NSEW", map[i][j]) && data->player.c == '0')
				data->player.c = map[i][j];
			j++;
		}
		i++;
	}
}

int	bottom_top_walls(char **map, int i, int j)
{
    if (map == NULL || map[i] == NULL)
        return (1);
    while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\v')
        j++;
    while (map[i][j])
    {
		printf("%c", map[i][j]);
		if (map[i][j + 1] == '\n' || map[i][j + 1] == '\0')
			break ;
        if (map[i][j] != '1')
            return (1);
        j++;
    }
    return (0);
}


// void	side_walls(t_map *data, char **map)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	if (bottom_top_walls(map, 0, 0) == 1)
// 	{
// 		printf("fail1\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	i = 1;
// 	while (i < (data->height))
// 	{
// 		j = ft_strlen(map[i]) - 1;
// 		if (map[i][0] != '1' || map[i][j] != '1')
// 		{
// 			printf("fail2\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	if (bottom_top_walls(map, i, 0) == 1)
// 	{
// 		printf("fail3\n");
// 		exit(EXIT_FAILURE);
// 	}
// }


void	side_walls(t_map *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (bottom_top_walls(map, i, 0) == 1)
	{
		printf("fail1\n");
		exit(EXIT_FAILURE);
	}
	i = 1;
	printf("[%d]\n", data->height);
	while (i < (data->height - 1))
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] != '1')
		{
			printf("fail1\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (bottom_top_walls(map, i, 0) == 1)
		exit(EXIT_FAILURE);
}

void	check_map_contents(t_data *data, char **map)
{
	if (data->map_info.map == NULL)
		exit(EXIT_FAILURE);
	// printf("%d\n", data->map_info.width);
	side_walls(&data->map_info, map);
	if (data->map_info.height < 3)
	{
		printf("Error! Map!\n");
		exit(EXIT_FAILURE);
	}
	// map_content_check(data, map);
}
