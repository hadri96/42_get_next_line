/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:26:06 by hmorand           #+#    #+#             */
/*   Updated: 2023/10/26 14:26:26 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_reader
{
	int		fd;
	int		buffer_location;
	int		buffer_size;
	char	buffer[BUFFER_SIZE];
	int		is_open;
}	t_reader;

char		*get_next_line(int fd);
t_reader	current_file(int fd, t_reader (*files)[10]);
void		ft_putstr_fd(char *s, int fd);
void		update_reader(t_reader current, int fd, t_reader (*files)[10]);
int			search_end_line(t_reader *current, int size_buff);

#endif
