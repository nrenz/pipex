/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:05:38 by nrenz             #+#    #+#             */
/*   Updated: 2022/11/10 16:42:10 by nrenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*trim_path(char *path_string)
{
	char	*trim_set;
	char	*trimmed_path;

	trim_set = "PATH=";
	trimmed_path = ft_strtrim(path_string, trim_set);
	return (trimmed_path);
}

char	**split_path(char *trimmed_path)
{
	char	**splited_path;
	char	delim;

	delim = ':';
	splited_path = ft_split(trimmed_path, delim);
	return (splited_path);
}

/* if found "path=" put in path_string, trim and split the path_string */
char	**find_path(t_pipex *pipex)
{
	int		i;
	char	*path_string;
	char	*trimmed_path;
	char	**splited_path;

	i = 0;
	while (pipex->envp[i] != NULL)
	{
		if (ft_strnstr(pipex->envp[i], "PATH=", 5))
		{
			path_string = ft_strnstr(pipex->envp[i], "PATH=", 5);
			trimmed_path = trim_path(path_string);
			splited_path = split_path(trimmed_path);
			return (splited_path);
		}
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char **splited_path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	while (splited_path[i])
	{
		tmp = ft_strjoin(splited_path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	**split_cmd_words(char *cmd)
{
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, ' ');
	if (cmd == NULL)
		return (NULL);
	return (splited_cmd);
}

char	**path_cmd_handling(t_pipex *pipex, int num)
{
	pipex->splited_path = find_path(pipex);
	pipex->cmd = split_cmd_words(pipex->argv[2 + num]);
	pipex->cmd_path = find_cmd_path(pipex->splited_path, pipex->cmd[0 + num]);
	return (NULL);
}
