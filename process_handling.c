/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:49:34 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/24 10:18:50 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_cmd_handling(t_pipex *pipex, int num)
{
	pipex->splited_path = find_path(pipex);
	pipex->cmd = split_cmd_words(pipex->argv[2 + num]);
	pipex->cmd_path = find_cmd_path(pipex->splited_path, pipex->cmd[0]);
	return (NULL);
}

/* parameter options:0 => waitpid() behave like wait() */
/* wexitstatus: translate bitmaske in error code 
	(int-wert => status / 256) */
void	splitting_process(t_pipex *pipex)
{
	int	status;

	pipe(pipex->pipe);
	status = 0;
	if (pipex->error == 0)
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			error_splitting_process(pipex);
		else if (pipex->pid1 == 0)
		{
			child(pipex, 0);
		}	
	}
	else
		error_splitting_process(pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		child(pipex, 1);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 1);
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	pipex->error = WEXITSTATUS(status);
}

/* 	output of 1st cmd will redirected to pipe-beginning 
	then will redirected to fd[0]
	read-part will redirected to pipe-ending
	after will redirected to fd_out */
void	child(t_pipex *pipex, int num)
{
	if (num == 0)
	{
		dup2(pipex->pipe[1], STDOUT_FILENO);
		dup2(pipex->fd_in, STDIN_FILENO);
		printf("%d\n", pipex->fd_in);
		close(pipex->fd_in);
		close(pipex->pipe[0]);
		path_cmd_handling(pipex, 0);
		printf("%d\n", num);
		run_shellcmd(pipex);
	}
	else
	{
		dup2(pipex->pipe[0], STDIN_FILENO);
		dup2(pipex->fd_out, STDOUT_FILENO);
		close(pipex->fd_out);
		close(pipex->pipe[1]);
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
