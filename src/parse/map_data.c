/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:29:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/12 19:20:19 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*get_path(char *map, int j)
{
	int		i;
	int		length;
	char	*path;

	length = 1;
	i = 0;
	while (map[j] && (map[j] == ' ' || map[j] == '\t'))
		j++;
	while (map[length] && (map[length] != ' ' || map[length] != '\t'))
		length++;
	path = malloc(sizeof(char) * (length - j + 1));
	if (path == NULL)
		return (NULL);
	while (map[j] && (map[j] != ' ' && map[j] != '\t' && map[j] != '\n'))
		path[i++] = map[j++];
	path[i] = '\0';
	while (map[j] && (map[j] == ' ' || map[j] == '\t'))
		j++;
	if (map[j] && (map[j] != '\n'))
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	set_path(t_map *texture, char **tex_path)
{
	int	i;

	i = 0;
	while (tex_path[i])
	{
		if (tex_path[i][0] == 'W' && tex_path[i][1] == 'E')
			texture->path_texture_west = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'S' && tex_path[i][1] == 'O')
			texture->path_texture_south = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'E' && tex_path[i][1] == 'A')
			texture->path_texture_east = get_path(tex_path[i], 2);
		else if (tex_path[i][0] == 'N' && tex_path[i][1] == 'O')
			texture->path_texture_north = get_path(tex_path[i], 2);
		else
			return (1);
		i++;
	}
	if (!texture->path_texture_north || !texture->path_texture_east || !texture->path_texture_south
			|| !texture->path_texture_west)
			return (1);
	return (0);
}

int	map_data(t_data *data)
{
	if (set_path(&data->map, data->texture.tex_path) == 1)
		return(error_msg("Failed to get texture path!", 1));
	// if (set_colot(data, data->texture.rgb_codes) == 1)
	// 	return (error_msg("Failed to get color codes!", 1));
	return (0);
}
