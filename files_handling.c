/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:43:59 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/18 15:17:17 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_files(t_pipex *pipex, char **argv)
{
	pipex->argv = argv;
	pipex->error = 0;
	open_infile(pipex);
	open_outfile(pipex);
	// printf("%d\n, %d\n", pipex->fd_in, pipex->fd_out);
	if (pipex->error)
		error_handling(pipex);
}

/* 	check memory leaks */
/* 	creat a function that free and exit the program */
/* 	dev/null is a special file
	called the null device in Unix systems */
void	open_infile(t_pipex *pipex)
{
	pipex->infile = pipex->argv[1];
	if (access(pipex->argv[1], F_OK) == -1)
		pipex->error = 1;
	else if (access(pipex->argv[1], R_OK) == -1)
		pipex->error = 2;
	else
		pipex->fd_in = open(pipex->argv[1], O_RDONLY);
}

/* 	O_TRUNC: file is successfully opened O_RDWR or O_WRONLY
	its length shall be truncated to 0
	and the mode and owner shall be unchanged */
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

// int	main(void)
// {
	
// }