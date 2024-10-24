/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:39:58 by ryusupov          #+#    #+#             */
/*   Updated: 2024/10/24 15:34:42 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	play_sound(pthread_t *thread, void *(*play)(void *))
{
	pthread_create(thread, NULL, play, NULL);
	pthread_detach(*thread);
}
