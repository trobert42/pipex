/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:47:32 by zerudo            #+#    #+#             */
/*   Updated: 2022/09/26 10:49:06 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

char	*get_path_envp(char **envp)
{
	char	*path_envp;

	path_envp = NULL;
	while (path_envp == NULL)
	{
		if (!*envp)
		{
			ft_putstr_fd("The env is NULL or pls set the PATH back\n", 2);
			exit(EXIT_FAILURE);
		}
		else
			path_envp = ft_strnstr(*envp++, "PATH", 4);
	}
	return (path_envp);
}

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
