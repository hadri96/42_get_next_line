/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:22:43 by hmorand           #+#    #+#             */
/*   Updated: 2023/10/14 17:07:39 by hmorand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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

int	process_buffer(t_reader **curr, int j, int i, char *line)
{
	if (j == (*curr)->buffer_size && line[i - 1] != '\n')
	{
		(*curr)->buffer_location = 0;
		(*curr)->buffer_size = read((*curr)->fd, (*curr)->buffer, BUFFER_SIZE);
	}
	else if (j < (*curr)->buffer_size)
		(*curr)->buffer_location = j;
	else
		(*curr)->buffer_location = 0;
	return ((*curr)->buffer_size);
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
		j = search_end_line(current, size_buff);
		line = app_str(line, &current, &i, j);
		if (!line)
			return (NULL);
		size_buff = process_buffer(&current, j, i, line);
		if (line[i - 1] == '\n')
			break ;
	}
	current->buffer_size = size_buff;
	return (line);
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
		return (NULL);
	}
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
