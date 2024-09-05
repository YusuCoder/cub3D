/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:19:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/03/11 16:46:36 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = str;
	i = 0;
	if (len != 0)
	{
		while (i < len)
		{
			ptr[i] = 0;
			i++;
		}
	}
}
