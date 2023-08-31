/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:34:30 by trobert           #+#    #+#             */
/*   Updated: 2022/04/19 14:45:20 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/superlibft.h"
/*
int	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}*/

char	*ft_cattoline(char *buff, char *line)
{
	int			i;
	int			j;
	char		*new;

	new = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buff) + 1));
	if (new == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (line[i])
	{
		new[i] = line[i];
		i++;
	}
	free(line);
	while (buff[j] && buff[j] != '\n' && j < BUFFER_SIZE)
		new[i++] = buff[j++];
	if (buff[j] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*ft_strdup_gnl(char *s, int src_len)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (src_len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_isline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_trim(char *buff, int ret, int checkfd)
{
	int	i;
	int	j;

	if (ret < BUFFER_SIZE && ft_isline(buff) == 0 && checkfd == 1)
		buff[0] = '\0';
	else if (checkfd == 1)
	{
		i = 0;
		j = 0;
		while ((buff[i] != '\n' && i < BUFFER_SIZE))
			i++;
		i++;
		while (buff[i])
			buff[j++] = buff[i++];
		buff[j] = '\0';
	}
}
