/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extracting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:03:28 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/12 18:19:55 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	extract_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->texture.tex_path = (char **)malloc(sizeof(char *) * 5);
	if (!data->texture.tex_path)
		error_msg("Malloc error!", 1);
	while (data->map.map_file[i])
	{
		if (ft_strncmp(data->map.map_file[i], "NO", 2) == 0 ||
			ft_strncmp(data->map.map_file[i], "SO", 2) == 0 ||
			ft_strncmp(data->map.map_file[i], "EA", 2) == 0 ||
			ft_strncmp(data->map.map_file[i], "WE", 2) == 0)
		{
			data->texture.tex_path[j] = ft_strdup(data->map.map_file[i]);
			if (!data->texture.tex_path[j])
			{
				while (--j >= 0)
					free(data->texture.tex_path[j]);
				free(data->texture.tex_path);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
		if (j == 4)
			break ;
	}
	data->texture.tex_path[j] = NULL;
}

void	extract_color(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->texture.rgb_codes = (char **)malloc(sizeof(char *) * 3);
	if (!data->texture.rgb_codes)
		exit(EXIT_FAILURE);
	while (data->map.map_file[i])
	{
		if (ft_strncmp(data->map.map_file[i], "F", 1) == 0 ||
			ft_strncmp(data->map.map_file[i], "C", 1) == 0)
		{
			data->texture.rgb_codes[j] = ft_strdup(data->map.map_file[i]);
			if (!data->texture.rgb_codes[j])
			{
				while (--j >= 0)
					free(data->texture.rgb_codes[j]);
				free(data->texture.rgb_codes);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	data->texture.rgb_codes[j] = NULL;
}
