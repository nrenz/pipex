/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:29:35 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/18 15:13:42 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handling(t_pipex *pipex)
{
	if (pipex->error == 1)
	{
		perror("input file does not exist");
		exit(1);
	}
	else if (pipex->error == 2)
	{
		perror("input file is not readable");
		exit(1);
	}
	else if (pipex->error == 3)
	{
		perror("invalid output file");
		exit(1);
	}
	else if (pipex->error == 4)
	{
		perror("Error: dup2 works incorrect");
		exit(1);
	}
	else if (pipex->error == 5)
	{
		perror("Error: invalid pipe");
		exit(1);
	}
	else if (pipex->error == 6)
	{
		perror("Error: fork function does not work");
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
