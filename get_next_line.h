/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:05:30 by hmorand           #+#    #+#             */
/*   Updated: 2023/10/14 10:41:53 by hmorand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_reader
{
	int		fd;
	int		buffer_location;
	int		buffer_size;
	char	buffer[BUFFER_SIZE];
	bool	done;
}	t_reader;

char		*get_next_line(int fd);
//t_reader	current_file(int fd, t_reader (*files)[10]);
//void		reset_reader(t_reader *files[10], int fd);
//void		update_reader(t_reader current, int fd, t_reader (*files)[10]);

#endif
