/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:42:19 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 17:31:46 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc(t_redirector *redirector, t_gen_data *data)
{
	char	*full_path;
	char	*file_index;
	int		fd;

	heredoc_count(data);
	file_index = ft_itoa(data->heredoc_count - 1);
	full_path = ft_strjoin("./tmp/heredoc_tmp_", file_index);
	fd = open(full_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(redirector->target_file, 2);
		ft_putendl_fd(": no such file or directory", 2);
		free(file_index);
		free(full_path);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	free(file_index);
	free(full_path);
	return (0);
}

int	append(t_redirector *redirector)
{
	int		fd;

	fd = open(redirector->target_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(redirector->target_file, 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	to_output(t_redirector *redirector)
{
	int	fd;

	fd = open(redirector->target_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(redirector->target_file, 2);
		ft_putendl_fd("no such file or directory", 2);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	from_input(t_redirector *redirector)
{
	int	fd;

	fd = open(redirector->target_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(redirector->target_file, 2);
		ft_putendl_fd(": no such file or directory", 2);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	redirect_setup(t_command *command, t_gen_data *data)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (command->redirections[i])
	{
		if (command->redirections[i]->type == INPUT)
			status = from_input(command->redirections[i]);
		else if (command->redirections[i]->type == OUTPUT)
			status = to_output(command->redirections[i]);
		else if (command->redirections[i]->type == APPEND)
			status = append(command->redirections[i]);
		else if (command->redirections[i]->type == HEREDOC)
			status = heredoc(command->redirections[i], data);
		i++;
	}
	return (status);
}