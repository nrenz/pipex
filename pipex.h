/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:44:27 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/02 14:43:52 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"
/* include definitions for type t_pid */
# include <sys/types.h>
/* define the following symbolic constants for use with waitpid() */
# include <sys/wait.h>
/* header for functions open() */
# include <fcntl.h>
/* header für mode_t  */
# include <sys/stat.h>

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**argv;
	char	**path;
	char	**envp;
	char	**splited_path;
	char	**cmd;
	char	*infile;
	char	*outfile;
	int		error;
	int		num_commands;
}			t_pipex;

/* 	functions for finding "path=", trim path and
	split the path in path_strings and find cmd_path */
char	**find_path(t_pipex *pipex);
char	*trim_path(char *path_string);
char	**split_path(char *trimmed_path);
char	*find_cmd_path(char **splited_path, char *cmd);
// void	free_pipex(t_pipex *pipex);

/* initialize files */
void	init_files(t_pipex *pipex, char **argv);
void	open_infile(t_pipex *pipex);
void	open_outfile(t_pipex *pipex);

/* error handling */
void	error_handling_file(t_pipex *pipex);
#endif