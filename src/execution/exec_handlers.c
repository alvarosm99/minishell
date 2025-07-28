/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:20:55 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 16:20:55 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*builtin_finder(char *executable)
{
	if (!ft_strcmp(executable, "echo"))
		return ("echo");
	else if (!ft_strcmp(executable, "cd"))
		return ("cd");
	else if (!ft_strcmp(executable, "env"))
		return ("env");
	else if (!ft_strcmp(executable, "exit"))
		return ("exit");
	else if (!ft_strcmp(executable, "export"))
		return ("export");
	else if (!ft_strcmp(executable, "pwd"))
		return ("pwd");
	else if (!ft_strcmp(executable, "unset"))
		return ("unset");
	else
		return (NULL);
}

int	execve_handler(t_command *command, char **env)
{
	char	*cmd_path;
	int		status;

	if (!command->argv)
		return (0);
	cmd_path = ft_get_path(command->argv[0], env);
	if (!cmd_path)
	{
		ft_putstr_fd("couldn't find command: ", 2);
		ft_putendl_fd(command->argv[0], 2);
		free(cmd_path);
		return (127);
	}
	status = execve(cmd_path, command->argv, env);
	if (status == -1)
	{
		ft_putstr_fd("command found but not executable: ", 2);
		ft_putendl_fd(command->argv[0], 2);
		free(cmd_path);
		return (126);
	}
	return (status);
}

int	execute_env_command(t_command *command, t_gen_data *data, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		fatal_error(data, "fork");
	else if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		data->last_exit_status = redirect_setup(command, data);
		{
			if (data->last_exit_status != 0)
				exit(data->last_exit_status);
		}
		data->last_exit_status = execve_handler(command, env);
		exit(data->last_exit_status);
	}
	else
	{
		g_signal_status = 1;
		wait(&data->last_exit_status);
		if (WIFSIGNALED(data->last_exit_status))
		{
			if (WTERMSIG(data->last_exit_status) == SIGINT)
				write(1, "\n", 1);
		}
	}
	return (data->last_exit_status);
}

int	builtin_handler(char *builtin, t_command *command, t_gen_data *data, char **env_list)
{
	if (!ft_strcmp(builtin, "echo"))
		return (echo(data, command));
	else if (!ft_strcmp(builtin, "cd"))
		return (cd(command->argv));
	else if (!ft_strcmp(builtin, "env"))
		return (env(env_list));
	else if (!ft_strcmp(builtin, "exit"))
		return (exit_minishell(data, command->argv));
	else if (!ft_strcmp(builtin, "export"))
		return (export(data, command->argv, env_list));
	else if (!ft_strcmp(builtin, "pwd"))
		return (pwd(data));
	else if (!ft_strcmp(builtin, "unset"))
		return (unset(data, command->argv));
	else
		return (-1);
}

int	execute_builtin(char *builtin, t_command *command, t_gen_data *data, char **env)
{
	pid_t	pid;

	if (data->redir_count > 0 && ft_strcmp(builtin, "cd") && ft_strcmp(builtin, "exit")
		&& ft_strcmp(builtin, "export") && ft_strcmp(builtin, "unset"))
	{
		pid = fork();
		if (pid < 0)
			fatal_error(data, "fork");
		else if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			data->last_exit_status = redirect_setup(command, data);
			{
				if (data->last_exit_status != 0)
					exit(data->last_exit_status);
			}
			data->last_exit_status = builtin_handler(builtin, command, data, env);
			exit(data->last_exit_status);
		}
		else
			wait(&data->last_exit_status);
		return (data->last_exit_status);
	}
	data->last_exit_status = builtin_handler(builtin, command, data, env);
	return (data->last_exit_status);
}
