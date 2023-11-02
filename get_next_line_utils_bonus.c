/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:26:33 by hmorand           #+#    #+#             */
/*   Updated: 2023/10/26 14:26:48 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_reader	current_file(int fd, t_reader (*files)[4096])
{
	int	i;

	i = 0;
	while ((*files)[i].is_open != 0 && (*files)[i].fd != fd && i < 4096)
		i++;
	if (i == 4096)
		i--;
	if ((*files)[i].is_open == 0)
	{
		(*files)[i].fd = fd;
		(*files)[i].is_open = 1;
	}
	return ((*files)[i]);
}

void	update_reader(t_reader current, int fd, t_reader (*files)[4096])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*files)[i].is_open != 0)
	{
		if (fd == (*files)[i].fd)
			break ;
		i++;
	}
	if (current.buffer_location)
	{
		(*files)[i].buffer_location = current.buffer_location;
		(*files)[i].buffer_size = current.buffer_size;
		while (j + current.buffer_location < current.buffer_size)
		{
			(*files)[i].buffer[j] = current.buffer[j + current.buffer_location];
			j++;
		}
		while (j < current.buffer_size)
			(*files)[i].buffer[j++] = '\0';
	}
	else
		(*files)[i].buffer_location = 0;
}

int	search_end_line(t_reader *current, int size_buff)
{
	int	i;

	i = 0;
	current->buffer_size = size_buff;
	while (i < size_buff)
	{
		if (current->buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
