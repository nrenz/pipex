/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:49:34 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/18 15:27:14 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* line35: parameter options: 
		0 => waitpid() behave like wait() */
/* line36: translate bitmaske in error code 
		(int-wert => status / 256) */
void	split_process(t_pipex *pipex)
{
	int	status;

	if (pipe(pipex->pipes) == -1)
		pipex->error = 5;
	pipe(pipex->pipes);
	status = 0;
	if (pipex->error == 0)
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			pipex->error = 6;
		else if (pipex->pid1 == 0)
		{
			child(pipex, 0);
		}	
	}
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		child(pipex, 1);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 1);
	// close(pipex->pipes[0]);
	// close(pipex->pipes[1]);
	pipex->error = WEXITSTATUS(status);
}

/* 	line36-37: output of 1st cmd will redirected to pipe-beginning 
	then will redirected to fd[0]
	line46-47: read-part will redirected 
	pipe-ending will redirected to fd_out */
void	child(t_pipex *pipex, int num)
{
	if (num == 0)
	{
		dup2(pipex->pipes[1], STDOUT_FILENO);
		dup2(pipex->fd_in, STDIN_FILENO);
		close(pipex->fd_in);
		close(pipex->pipes[0]);
		path_cmd_handling(pipex, 0);
		run_shellcmd(pipex);
	}
	else
	{
		dup2(pipex->pipes[0], STDIN_FILENO);
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
		close(pipex->pipes[1]);
		path_cmd_handling(pipex, 1);
		run_shellcmd(pipex);
	}
}

/* error 127 => cmd not found */
void	run_shellcmd(t_pipex *pipex)
{
	execve(pipex->cmd_path, pipex->cmd, pipex->envp);
	error_shellcmd(pipex, 127);
}

// void	free_split_process(t_pipex *pipex)
// {
// 	int	index;

// 	index = 0;
// 	while (index < pipex->num_commands[index]-> )
// }
