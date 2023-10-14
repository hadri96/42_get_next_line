/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:22:43 by hmorand           #+#    #+#             */
/*   Updated: 2023/10/14 15:57:04 by hmorand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return ;
	}
	while (*s)
		write(fd, s++, 1);
}

int	search_line(char *buffer, int size_buff)
{
	int	i;

	i = 0;
	while (i < size_buff)
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*app_str(char *line, t_reader **current, int *i, int j)
{
	char	*new_str;
	int		pos;

	new_str = malloc(*i + 1 + j);
	if (!new_str)
	{
		free(line);
		return (NULL);
	}
	pos = -1;
	while (++pos < *i)
		new_str[pos] = line[pos];
	free(line);
	pos--;
	while (++pos < *i + j)
		new_str[pos] = (*current)->buffer[pos - *i];
	*i = pos;
	new_str[*i] = '\0';
	return (new_str);
}

char	*extract_line(int fd, t_reader *current)
{
	char	*line;
	int		size_buff;
	int		i;
	int		j;

	if (current->buffer_location == 0)
		size_buff = read(fd, current->buffer, sizeof(current->buffer));
	else
		size_buff = current->buffer_size - current->buffer_location;
	i = 0;
	if (size_buff < 0)
		return (NULL);
	line = NULL;
	while (size_buff)
	{
		j = search_line(current->buffer, size_buff);
		line = app_str(line, &current, &i, j);
		if (!line)
			return (NULL);
		if (j == size_buff && line[i - 1] != '\n')
		{
			current->buffer_location = 0;
			size_buff = read(fd, current->buffer, sizeof(current->buffer));
		}
		else if (j < size_buff)
			current->buffer_location = j;
		if (line[i - 1] == '\n')
			break;
	}
	current->buffer_size = size_buff;
	return (line);
}

t_reader	current_file(int fd, t_reader (*files)[10])
{
	int	i;

	i = 0;
	while ((*files)[i].is_open != 0 && (*files)[i].fd != fd && i < 10)
		i++;
	if (i == 10)
		i--;
	if ((*files)[i].is_open == 0)
	{
		(*files)[i].fd = fd;
		(*files)[i].is_open = 1;
	}
	return ((*files)[i]);
}

void	update_reader(t_reader current, int fd, t_reader (*files)[10])
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

char	*get_next_line(int fd)
{
	static t_reader	files[10] = {0};
	t_reader		current;
	char			*line;

	current = current_file(fd, &files);
	line = extract_line(fd, &current);
	update_reader(current, fd, &files);
	if (!line)
	{
		free(line);
		// ft_putstr_fd("line: ", 1);
		// ft_putstr_fd(line, 1);
		// ft_putstr_fd("\n", 1);
		return (NULL);
	}
	// ft_putstr_fd("line: ", 1);
	// ft_putstr_fd(line, 1);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	int fd2;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("Error", 1);
// 		return (0);
// 	}
// 	fd2 = open("test1.txt", O_RDONLY);
// 	if (fd2 == -1)
// 	{
// 		ft_putstr_fd("Error", 1);
// 		return (0);
// 	}
// 	printf("Buffer size: %d\n", BUFFER_SIZE);
// 	printf("fd: %d\n", fd);
// 	printf("fd2: %d\n", fd2);
// 	printf("------------------------\n");
// 	printf("fd\n");
// 	get_next_line(fd);
// 	printf("------------------------\n");
// 	printf("fd2\n");
// 	get_next_line(fd2);
// 	printf("------------------------\n");
// 	printf("fd2\n");
// 	get_next_line(fd2);
// 	printf("------------------------\n");
// 	printf("fd2\n");
// 	get_next_line(fd2);
// 	printf("------------------------\n");
// 	printf("fd2\n");
// 	get_next_line(fd2);
// 	printf("------------------------\n");
// 	printf("fd\n");
// 	get_next_line(fd);
// 	printf("------------------------\n");
// 	printf("fd\n");
// 	get_next_line(fd);
// 	printf("------------------------\n");
// 	printf("fd\n");
// 	get_next_line(fd);
// 	printf("------------------------\n");
// 	printf("fd\n");
// 	get_next_line(fd);
// }

