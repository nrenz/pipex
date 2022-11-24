/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:43:59 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/24 10:15:16 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_files(t_pipex *pipex, char **argv)
{
	pipex->argv = argv;
	pipex->error = 0;
	open_infile(pipex);
	open_outfile(pipex);
	if (pipex->error)
		error_files_handling(pipex);
}

void	open_infile(t_pipex *pipex)
{
	pipex->infile = pipex->argv[1];
	if (access(pipex->argv[1], F_OK) == -1)
		pipex->error = 1;
	else if (access(pipex->argv[1], R_OK) == -1)
		pipex->error = 2;
	else
	{
		pipex->fd_in = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd_in == -1)
			pipex->error = 2;
	}
}

/* 	0644 rights: 
	User: read & write
	Group: read
	Other: read */
void	open_outfile(t_pipex *pipex)
{
	pipex->outfile = pipex->argv[pipex->argc - 1];
	pipex->fd_out = open(pipex->argv[pipex->argc - 1], \
						O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
		pipex->error = 3;
}
