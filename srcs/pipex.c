/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:43 by zerudo            #+#    #+#             */
/*   Updated: 2022/05/04 10:56:30 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_cmd(t_data *data, char *argv, char **envp)
{
	int	i;

	i = 0;
	data->path_envp = get_path_envp(envp);
	data->potential_paths = ft_split(data->path_envp + 5, ':');
	if (!data->potential_paths)
		error_free_quit(data, "malloc for potential_paths has failed\n", 1);
	data->cmd = get_cmd(data, argv);
	while (data->potential_paths[i])
	{
		data->path_cmd = ft_cmdjoin(data->potential_paths[i], data->cmd[0]);
		if (!data->path_cmd)
			error_free_quit(data, "malloc in ft_cmdjoin has failed\n", 2);
		data->spe_cmd = ft_split(argv, ' ');
		if (execve(data->path_cmd, data->cmd, envp) < 0)
			free(data->path_cmd);
		if (execve(data->spe_cmd[0], data->spe_cmd, envp) < 0)
			free_split(data->spe_cmd);
		i++;
	}
	error_free_quit(data, "command not found: ", 3);
}

void	child1_process(t_data *data, int *pipefd, char **argv, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		error_free_quit(data, "Error with fork\n", 1);
	if (data->pid1 == 0)
	{
		open_infile(data, argv[1]);
		close(pipefd[0]);
		if (dup2(data->infile_fd, STDIN_FILENO) < 0)
			error_free_quit(data, "dup2 for infile_fd has failed\n", 1);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			error_free_quit(data, "dup2 for pipefd[1] has failed\n", 1);
		execute_cmd(data, argv[2], envp);
	}
}

void	child2_process(t_data *data, int *pipefd, char **argv, char **envp)
{
	data->pid2 = fork();
	if (data->pid2 < 0)
		error_free_quit(data, "Error with fork\n", 1);
	if (data->pid2 == 0)
	{
		open_outfile(data, argv[4]);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			error_free_quit(data, "dup2 for pipefd[0] has failed\n", 1);
		if (dup2(data->outfile_fd, STDOUT_FILENO) < 0)
			error_free_quit(data, "dup2 for outfile_fd has failed\n", 1);
		execute_cmd(data, argv[3], envp);
	}
}

void	pipex(t_data *data, char **argv, char **envp)
{
	int	pipefd[2];
	int	status;

	if (pipe(pipefd) == -1)
		error_free_quit(data, "Error with pipe(pipefd)\n", 1);
	child1_process(data, pipefd, argv, envp);
	close(pipefd[1]);
	child2_process(data, pipefd, argv, envp);
	close_all_pipes(data, pipefd);
	waitpid(data->pid1, &status, 0);
	waitpid(data->pid2, &status, 0);
	free_all(data);
	if (status != 0)
		exit(WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		error_free_quit(&data, "Try: ./pipex infile cmd1 cmd2 outfile\n", 1);
	else
	{
		init_var(&data);
		data.path_envp = get_path_envp(envp);
		pipex(&data, argv, envp);
	}
	return (0);
}
