/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:44:57 by trobert           #+#    #+#             */
/*   Updated: 2022/05/02 14:59:19 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H 

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
	int		cmd_nbr;
	int		pipe_nbr;
	char	*path_envp;
	char	**potential_paths;
	char	*path_cmd;
	char	**spe_cmd;
	char	**cmd;
	char	*limiter;
	int		hered_fd;
	int		hered_flag;
	int		infile_fd;
	int		outfile_fd;
	int		argc;
	int		index;
	int		status;
	int		**pipefd;
	int		*pid;
}	t_data;

//----------INIT VAR----------------------------------------
void		init_var(t_data *data, int argc, char **envp);
void		pipex(t_data *data, char **argv, char **envp);

//----------HERE_DOC FUNCTIONS------------------------------
int			is_same_str(char *s1, char *s2);
void		hered_mode(t_data *data, char **argv);
void		open_hered_outfile(t_data *data, char *argv);

//----------GET CMDS AND PATH FUNCTIONS---------------------
int			get_tab_size(char **tab);
char		**get_cmd(t_data *data, char *argv);
char		*ft_cmdjoin(char *s1, char *s2);
char		*get_path_envp(char **envp);
void		execute_cmd(t_data *data, char *argv, char **envp);

//----------FD FUNCTIONS------------------------------------
void		open_infile(t_data *data, char *argv);
void		open_outfile(t_data *data, char *argv);
void		close_pipes(t_data *data, int i);
void		close_all_pipes(t_data *data);
void		close_all_except_one(t_data *data);

//----------FREE AND EXIT FUNCTIONS-------------------------
int			free_split(char **tab);
int			free_split_int(int **tab, int i);
void		free_all(t_data *data);
void		msg_err_arg(t_data *data, char *str, char *argv, int flag);
void		error_free_quit(t_data *data, char *str, int flag);

#endif
