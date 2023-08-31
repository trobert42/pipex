/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/05/04 11:05:19 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	open_infile(t_data *data, char *argv)
{
	data->infile_fd = open(argv, O_RDONLY);
	if (data->infile_fd < 0)
		msg_err_arg(strerror(errno), argv, 1);
}

void	open_outfile(t_data *data, char *argv)
{
	data->outfile_fd = open(argv, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (data->outfile_fd < 0)
		msg_err_arg(strerror(errno), argv, 2);
}

void	close_all_pipes(t_data *data, int pipefd[2])
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close(pipefd[0]);
	close(pipefd[1]);
}
