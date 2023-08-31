/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/10/30 15:41:27 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	first_process(t_data *data, char **argv, char **envp)
{
	close_all_except_one(data);
	close(data->pipefd[data->index][0]);
	if (data->hered_flag == 1)
	{
		if (dup2(data->hered_fd, STDIN_FILENO) < 0)
			error_free_quit(data, "dup2 for hered_fd has failed\n", 1);
	}
	else
	{
		open_infile(data, argv[1]);
		if (dup2(data->infile_fd, STDIN_FILENO) < 0)
			error_free_quit(data, "dup2 for infile_fd has failed\n", 1);
	}
	if (dup2(data->pipefd[0][1], STDOUT_FILENO) < 0)
		error_free_quit(data, "dup2 for pipefd[1][1] has failed\n", 1);
	execute_cmd(data, argv[2 + data->hered_flag], envp);
}

void	nth_child(t_data *data, char *argv, char **envp)
{
	close(data->infile_fd);
	close_pipes(data, data->index);
	if (dup2(data->pipefd[data->index - 1][0], STDIN_FILENO) < 0)
		error_free_quit(data, "dup2 for nth child stdin has failed\n", 1);
	if (dup2(data->pipefd[data->index][1], STDOUT_FILENO) < 0)
		error_free_quit(data, "dup2 for nth child stdout has failed\n", 1);
	execute_cmd(data, argv, envp);
}

void	last_process(t_data *data, char **argv, char **envp)
{
	close(data->infile_fd);
	close(data->pipefd[data->cmd_nbr - 1][1]);
	close(data->pipefd[data->cmd_nbr - 1][0]);
	if (data->hered_flag == 1)
		open_hered_outfile(data, argv[data->argc - 1]);
	else
		open_outfile(data, argv[data->argc - 1]);
	if (dup2(data->pipefd[data->index - 1][0], STDIN_FILENO) < 0)
		error_free_quit(data, "dup2 for pipefd[i][0] has failed\n", 1);
	if (dup2(data->outfile_fd, STDOUT_FILENO) < 0)
		error_free_quit(data, "dup2 for outfile_fd has failed\n", 1);
	execute_cmd(data, argv[data->argc - 2], envp);
}

void	pipex(t_data *data, char **argv, char **envp)
{
	while (data->index < data->cmd_nbr)
	{
		data->pid[data->index] = fork();
		if (data->pid[data->index] < 0)
			error_free_quit(data, "Error with fork\n", 1);
		if (data->index == 0 && data->pid[data->index] == 0)
			first_process(data, argv, envp);
		if (data->index == data->cmd_nbr - 1 && data->pid[data->index] == 0)
			last_process(data, argv, envp);
		if (data->index != 0 && data->pid[data->index] == 0)
			nth_child(data, argv[data->index + 2], envp);
		close(data->pipefd[data->index][1]);
		data->index++;
	}
	close_all_pipes(data);
	data->index = -1;
	while (++data->index < data->cmd_nbr)
		waitpid(data->pid[data->index], &data->status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	i = 0;
	if (argc < 5)
	{
		write(2, "Args < 5\n", 10);
		exit(EXIT_FAILURE);
	}
	init_var(&data, argc, envp);
	data.path_envp = get_path_envp(envp);
	if (is_same_str(argv[1], "here_doc") == 1 && argc >= 5)
		hered_mode(&data, argv);
	while (i < data.cmd_nbr)
	{
		if (pipe(data.pipefd[i++]) == -1)
			error_free_quit(&data, "Error with pipe(pipefd)\n", 1);
	}
	pipex(&data, argv, envp);
	free_all(&data);
	if (data.status != 0)
		exit(WEXITSTATUS(data.status));
	return (0);
}
