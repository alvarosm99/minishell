/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:29:24 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 21:18:04 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>

int	too_many_args(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	cd_handler(char *path)
{
	if (chdir(path) != 0)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Permission denied", 2);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else if (errno == ENOTDIR)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Not a directory", 2);
		}
		else if (errno == ENAMETOOLONG)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": File name too long", 2);
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		return (1);
	}
	return (0);
}

int	cd(char **commands)
{
	char	*path;

	if (too_many_args(commands))
		return (1);
	if (!commands[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		chdir(path);
		return (0);
	}
	else
	{
		path = commands[1];
		return (cd_handler(path));
	}
}
