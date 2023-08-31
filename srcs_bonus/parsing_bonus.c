/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/04/12 16:18:11 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_var(t_data *data, int argc)
{
	int	i;

	i = 0;
	data->index = 0;
	data->argc = argc;
	data->cmd_nbr = argc - 3;
	data->pipe_nbr = argc - 4;
	data->path_envp = NULL;
	data->potential_paths = NULL;
	data->path_cmd = NULL;
	data->cmd = NULL;
	data->pid = (int *)malloc(sizeof(int) * data->cmd_nbr);
	while (i < data->cmd_nbr)
		data->pid[i++] = -1;
	i = 0;
	data->pipefd = (int **)malloc(sizeof(int *) * data->cmd_nbr);
	while (i < data->cmd_nbr)
	{
		data->pipefd[i] = (int *)malloc(sizeof(int) * 2);
		data->pipefd[i][0] = 0;
		data->pipefd[i][1] = 0;
		i++;
	}
}

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_cmdjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 2));
	if (!str)
		return (NULL);
	while (i < s1_len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (i < (s1_len + 1 + s2_len))
		str[i++] = s2[j++];
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}

char	**get_cmd(t_data *data, char *argv)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		free_split(data->potential_paths);
		error_free_quit(data, "malloc for cmd has failed\n", 1);
	}
	if (cmd && get_tab_size(cmd) == 0)
	{
		free(cmd);
		error_free_quit(data, "permission denied:\n", 2);
	}
	return (cmd);
}

char	*get_path_envp(t_data *data, char **envp)
{
	char	*path_envp;

	path_envp = NULL;
	while (path_envp == NULL)
	{
		if (!*envp)
			error_free_quit(data, "The env doesn't exist or is NULL\n", 1);
		path_envp = ft_strnstr(*envp++, "PATH", 4);
	}
	return (path_envp);
}
