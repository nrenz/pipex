/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:29:35 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/24 10:14:40 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_files_handling(t_pipex *pipex)
{
	if (pipex->error == 1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pipex->infile);
	}
	else if (pipex->error == 2)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pipex->infile);
		free(pipex);
		exit (0);
	}
	else if (pipex->error == 3)
	{
		ft_putstr_fd("pipex: ", 2);
		close (pipex->fd_in);
		perror(pipex->outfile);
		free(pipex);
		exit (1);
	}
}

void	error_handler_pipe(t_pipex *pipex)
{
	perror("pipex: ");
	free(pipex);
	exit(1);
}

void	error_splitting_process(t_pipex *pipex)
{
	if (pipex->error == 4)
	{
		perror("pipex: ");
		free(pipex);
		exit(1);
	}
	else if (pipex->error == 5)
	{
		perror("pipex: ");
		free(pipex);
		exit(1);
	}
	else if (pipex->error == 6)
	{
		perror("pipex: ");
		free(pipex);
		exit(1);
	}
	else if (pipex->error == 7)
	{
		perror("pipex: ");
		free(pipex);
		exit(1);
	}
}

void	error_shellcmd(t_pipex *pipex, int num)
{
	int	index;

	index = 0;
	if (pipex->path)
	{
		while (pipex->path[index])
			free(pipex->path[index++]);
		free(pipex->path);
	}
	free(pipex);
	exit (num);
}
