/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/05/02 15:04:27 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	get_limiter_str(t_data *data, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	data->limiter = (char *)malloc(sizeof(char) * (len + 2));
	if (!data->limiter)
		error_free_quit(data, "malloc for data->limiter has failed\n", 1);
	while (i < len)
	{
		data->limiter[i] = str[i];
		i++;
	}
	data->limiter[i++] = '\n';
	data->limiter[i] = '\0';
}

void	open_hered_outfile(t_data *data, char *argv)
{
	data->outfile_fd = open(argv, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (data->outfile_fd < 0)
	{
		if (errno == EACCES)
			msg_err_arg(data, "permission denied: ", argv, 2);
		else if (errno == ENOENT)
			msg_err_arg(data, "no such file or directory: ", argv, 2);
		else if (errno == ENOTDIR)
			msg_err_arg(data, "not a directory: ", argv, 2);
	}
}

void	hered_mode_gnl(t_data *data)
{
	char	*str;

	str = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 0);
		str = get_next_line(0);
		if (is_same_str(str, data->limiter) == 1)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, data->hered_fd);
		free(str);
	}
	free(data->limiter);
}

void	hered_mode(t_data *data, char **argv)
{
	data->hered_flag = 1;
	data->hered_fd = open(".hered_temp", O_WRONLY | O_CREAT, 0644);
	if (data->hered_fd < 0)
		error_free_quit(data, "open here_doc failed\n", 1);
	if (dup2(data->hered_fd, STDOUT_FILENO) < 0)
		error_free_quit(data, "dup2 for here_fd has failed\n", 1);
	get_limiter_str(data, argv[2]);
	hered_mode_gnl(data);
	close(data->hered_fd);
	data->hered_fd = open(".hered_temp", O_RDONLY, 0644);
}
