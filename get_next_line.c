/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:27 by hmorand           #+#    #+#             */
/*   Updated: 2023/09/18 09:41:09 by hmorand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

#include <stdio.h>

t_reader	current_file(int fd, t_reader (*files)[10])
{
	int	i;

	i = 0;
	while ((*files)[i].fd != -1 && (*files)[i].fd != fd)
		i++;
	if ((*files)[i].fd == -1)
		(*files)[i].fd = fd;
	return ((*files)[i]);
}

void	update_reader(t_reader current, int fd, t_reader (*files)[10])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*files)[i].fd != -1)
	{
		if (fd == (*files)[i].fd)
		{
			(*files)[i].buffer_location = current.buffer_location;
			(*files)[i].remaining = current.remaining;
			(*files)[i].fd = current.fd;
			while (current.buffer[j])
			{
				(*files)[i].buffer[j] = current.buffer[j];
				j++;
			}
			break ;
		}
		i++;
	}
}

void	reset_reader(t_reader *files[10], int fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*files)[i].fd != -1)
	{
		if (fd == (*files)[i].fd)
		{
			while ((*files)[i + j + 1].fd != -1)
			{
				(*files)[i + j] = (*files)[i + j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
	(*files)[i + j].fd = -1;
}

void	print_content(t_reader current)
{
	printf("------------------------\n");
	printf("Remaining buffer: %s\n", current.buffer);
	printf("------------------------\n");
	printf("Buffer location: %d\n", current.buffer_location);
}

char	*str_appstr(char *str, t_reader *curr, int size, int size_buff)
{
	char	*new_str;
	int		i;
	int		j;

	if ((*curr).buffer_location != BUFFER_SIZE)
		i = (*curr).buffer_location;
	else
		i = 0;
	j = i;
	while ((*curr).buffer[i] != '\n' && i - (*curr).buffer_location < size_buff)
		i++;
	if (i - (*curr).buffer_location < size_buff)
	{
		(*curr).remaining = size_buff - i - 1;
		size_buff = i + 1;
		(*curr).buffer_location = size_buff;
		(*curr).done = true;
	}
	else
	{
		(*curr).remaining = 0;
		(*curr).buffer_location = 0;
	}
	new_str = malloc(sizeof(char) * (size + size_buff) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < size)
		new_str[i] = str[i];
	free(str);
	i--;
	while (++i - size < size_buff)
		new_str[i] = (*curr).buffer[i + j - size];
	new_str[size + size_buff] = '\0';
	return (new_str);
}

char	*extract_line(int fd, t_reader *current)
{
	char	*line;
	int		size_buff;
	int		i;

	if (current->buffer_location == 0 || current->remaining == 0)
		size_buff = read(fd, current->buffer, sizeof(current->buffer));
	else
		size_buff = current->remaining;
	i = 0;
	line = malloc(sizeof(char) * i + 1);
	if (!line || size_buff == -1)
		return (NULL);
	current->done = false;
	while (size_buff)
	{
		line = str_appstr(line, current, i, size_buff);
		i += size_buff;
		if (current->done)
			break ;
		size_buff = read(fd, current->buffer, sizeof(current->buffer));
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static t_reader		files[10] = {{-1, 0, 0, "", false},
	{-1, 0, 0, "", false}, {-1, 0, 0, "", false}, {-1, 0, 0, "", false},
	{-1, 0, 0, "", false}, {-1, 0, 0, "", false}, {-1, 0, 0, "", false},
	{-1, 0, 0, "", false}, {-1, 0, 0, "", false}, {-1, 0, 0, "", false}};
	t_reader			current;
	char				*line;

	current = current_file(fd, &files);
	line = extract_line(fd, &current);
	update_reader(current, fd, &files);
	//print_content(current);
	if (!line[0])
	{
		free(line);
		printf("line: (null)\n");
		return (NULL);
	}
	printf("line: %s", line);
	return (line);
}

int	main(void)
{
	int	fd;
	int	fd2;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error");
		return (0);
	}
	fd2 = open("test.txt", O_RDONLY);
	if (fd2 == -1)
	{
		printf("Error");
		return (0);
	}
	printf("Buffer size: %d\n", BUFFER_SIZE);
	printf("fd: %d\n", fd);
	printf("fd2: %d\n", fd2);
	printf("------------------------\n");
	printf("fd\n");
	get_next_line(fd);
	printf("------------------------\n");
	printf("fd2\n");
	get_next_line(fd2);
	printf("------------------------\n");
	printf("fd2\n");
	get_next_line(fd2);
	printf("------------------------\n");
	printf("fd\n");
	get_next_line(fd);
	printf("------------------------\n");
	printf("fd\n");
	get_next_line(fd);
	printf("------------------------\n");
	printf("fd\n");
	get_next_line(fd);
	printf("------------------------\n");
	printf("fd\n");
	get_next_line(fd);
}
