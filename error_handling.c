/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:29:35 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/04 15:54:32 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_handling_file(t_pipex *pipex)
{
	if (pipex->error == 1)
	{
		perror("input file does not exist");
		// free(pipex->infile);
		exit(1);
	}
	else if (pipex->error == 2)
	{
		perror("input file is not readable");
		// free(pipex->infile);
		exit(1);
	}
	else if (pipex->error == 3)
	{
		perror("invalid output file");
		// free(pipex->outfile);
		close(pipex->fd_in);
		exit(1);
	}
}
