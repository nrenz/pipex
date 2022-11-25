/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:20 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/25 13:15:39 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5 || argc > 5)
		error_args();
	pipex = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (1);
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	if (!envp)
		return (0);
	pipex->error = 0;
	pipex->num_commands = argc - 3;
	init_files(pipex, argv);
	if (pipe(pipex->pipe) == -1)
		error_handler_pipe(pipex);
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	splitting_process(pipex);
	close(pipex->fd_in);
	close(pipex->fd_out);
	free (pipex);
	return (0);
}
