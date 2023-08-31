/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:44:57 by trobert           #+#    #+#             */
/*   Updated: 2022/05/04 10:55:16 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 

# include "superlibft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

typedef struct s_data
{
	char	*path_envp;
	char	**potential_paths;
	char	*path_cmd;
	char	**cmd;
	char	**spe_cmd;
	int		pid1;
	int		pid2;
	int		infile_fd;
	int		outfile_fd;
}	t_data;

void		init_var(t_data *data);
void		pipex(t_data *data, char **argv, char **envp);
void		open_infile(t_data *data, char *argv);
void		open_outfile(t_data *data, char *argv);
void		child1_process(t_data *data, int *pipefd, char **argv, char **envp);
void		child2_process(t_data *data, int *pipefd, char **argv, \
		char **envp);
char		**get_cmd(t_data *data, char *argv);
char		*get_path_envp(char **envp);
char		*ft_cmdjoin(char *s1, char *s2);
int			get_tab_size(char **tab);
void		execute_cmd(t_data *data, char *argv, char **envp);
void		msg_err_arg(char *str, char *argv, int flag);
void		close_all_pipes(t_data *data, int pipefd[2]);
void		error_free_quit(t_data *data, char *str, int flag);
int			free_split(char **tab);
void		free_all(t_data *data);

#endif
