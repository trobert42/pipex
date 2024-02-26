/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/04/20 15:08:51 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_pid(t_data *data)
{
	int	i;

	i = 0;
	data->pid = (int *)malloc(sizeof(int) * data->cmd_nbr);
	if (!data->pid)
	{
		ft_putstr_fd("malloc for pid in init_var failed\n", 2);
		exit(EXIT_FAILURE);
	}
	while (i < data->cmd_nbr)
		data->pid[i++] = -1;
}

void	init_pipefd(t_data *data)
{
	int	i;

	i = 0;
	data->pipefd = (int **)malloc(sizeof(int *) * data->cmd_nbr);
	if (!data->pipefd)
	{
		ft_putstr_fd("malloc for pipefd in init_var failed\n", 2);
		free(data->pid);
		exit(EXIT_FAILURE);
	}
	while (i < data->cmd_nbr)
	{
		data->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipefd[i])
		{
			ft_putstr_fd("malloc for pipefd in init_var failed\n", 2);
			free(data->pid);
			free_split_int(data->pipefd, i);
			exit(EXIT_FAILURE);
		}
		data->pipefd[i][0] = 0;
		data->pipefd[i][1] = 0;
		i++;
	}
}

void	init_var(t_data *data, int argc, char **envp)
{
	data->hered_flag = 0;
	data->index = 0;
	data->argc = argc;
	data->cmd_nbr = argc - 3;
	data->pipe_nbr = argc - 4;
	data->potential_paths = NULL;
	data->path_cmd = NULL;
	data->cmd = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->path_envp = get_path_envp(envp);
	init_pid(data);
	init_pipefd(data);
}
