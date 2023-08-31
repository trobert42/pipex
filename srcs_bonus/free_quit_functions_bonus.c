/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_quit_functions_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zerudo <zerudo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:57 by zerudo            #+#    #+#             */
/*   Updated: 2022/05/04 10:54:44 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}

int	free_split_int(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
	return (0);
}

void	msg_err_arg(t_data *data, char *str, char *argv, int flag)
{
	free_split_int(data->pipefd, data->cmd_nbr);
	free(data->pid);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, argv, ft_strlen(argv));
	write(2, "\n", 1);
	if (flag == 2)
		exit(EXIT_FAILURE);
	exit(0);
}

void	error_free_quit(t_data *data, char *str, int flag)
{
	free_split_int(data->pipefd, data->cmd_nbr);
	free(data->pid);
	if (flag == 1)
	{
		write(2, str, ft_strlen(str));
		exit(EXIT_FAILURE);
	}
	write(2, str, ft_strlen(str));
	if (flag == 3)
	{
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(2, "\n", 1);
		free_split(data->potential_paths);
		free_split(data->cmd);
		exit(127);
	}
	else if (flag == 2)
	{
		free_split(data->potential_paths);
		exit(EXIT_FAILURE);
	}
}

void	free_all(t_data *data)
{
	if (data->path_cmd)
		free(data->path_cmd);
	if (data->potential_paths)
		free_split(data->potential_paths);
	if (data->cmd)
		free_split(data->cmd);
	if (data->pid)
		free(data->pid);
	if (data->pipefd)
		free_split_int(data->pipefd, data->cmd_nbr);
	if (data->hered_flag == 1)
		close(data->hered_fd);
}
