/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:33:50 by trobert           #+#    #+#             */
/*   Updated: 2022/04/19 14:41:54 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/superlibft.h"

static int	ft_checkfd(int fd, int ret)
{
	if (fd == -1)
		return (0);
	if (ret == -1)
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		buff[1024][BUFFER_SIZE + 1];
	int				ret;

	if (ft_strlen(buff[fd]) == 0)
		ret = read(fd, buff[fd], BUFFER_SIZE);
	else
		ret = BUFFER_SIZE;
	line = malloc(sizeof(char));
	line[0] = '\0';
	while (ret && ft_checkfd(fd, ret) == 1)
	{
		buff[fd][ret] = '\0';
		line = ft_cattoline(buff[fd], line);
		if (ft_isline(line) == 1 || ret < BUFFER_SIZE)
			break ;
		ret = read(fd, buff[fd], BUFFER_SIZE);
	}
	ft_trim(buff[fd], ret, ft_checkfd(fd, ret));
	if ((ret == 0 && line[0] == '\0') || ft_checkfd(fd, ret) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
