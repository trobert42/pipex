/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_functions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/05/04 11:57:41 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	open_infile(t_data *data, char *argv)
{
	data->infile_fd = open(argv, O_RDONLY);
	if (data->infile_fd < 0)
		msg_err_arg(data, strerror(errno), argv, 1);
}

void	open_outfile(t_data *data, char *argv)
{
	data->outfile_fd = open(argv, O_CREAT | O_WRONLY, 0644);
	if (data->outfile_fd < 0)
		msg_err_arg(data, strerror(errno), argv, 2);
}

void	close_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->cmd_nbr)
	{
		if (j != i)
			close(data->pipefd[j][1]);
		if (j != i - 1)
			close(data->pipefd[j][0]);
		j++;
	}
}

void	close_all_except_one(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->cmd_nbr)
	{
		close(data->pipefd[i][0]);
		close(data->pipefd[i][1]);
		i++;
	}
}

void	close_all_pipes(t_data *data)
{
	int	i;

	i = -1;
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	while (++i < data->cmd_nbr)
	{
		close(data->pipefd[i][0]);
		close(data->pipefd[i][1]);
	}
	unlink(".hered_temp");
}
