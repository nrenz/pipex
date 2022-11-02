/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:59:20 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/02 14:45:42 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		ft_putstr_fd("invalid number of arguments\n", 2);
		return (1);
	}
	pipex = (t_pipex *)calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (1);
	pipex->argc	= argc;
	pipex->argv = argv;
	pipex->envp = envp;
	if (!envp)
		return (0);
	pipex->splited_path = find_path(pipex);
	// pipex->cmd = 
	pipex->error = 0;
	pipex->num_commands = argc - 3;
}
