/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:47:54 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 17:56:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	load_export(t_gen_data *data, char **env)
{
	int	i;

	if (!env)
		fatal_error(data, "env");
	i = 0;
	while (env[i])
		i++;
	data->exec_env_export = malloc(sizeof(char *) * (i + 1));
	if (!data->exec_env_export)
		fatal_error(data, "malloc");
	data->exec_env_export[i] = NULL;
	i = 0;
	while (env[i])
	{
		data->exec_env_export[i] = ft_strdup(env[i]);
		if (!data->exec_env_export[i])
			fatal_error(data, "malloc");
		i++;
	}
}

void	load_env(t_gen_data *data, char **env)
{
	int	i;

	if (!env)
		fatal_error(data, "env");
	i = 0;
	while (env[i])
		i++;
	data->exec_env = malloc(sizeof(char *) * (i + 1));
	if (!data->exec_env)
		fatal_error(data, "malloc");
	data->exec_env[i] = NULL;
	i = 0;
	while (env[i])
	{
		data->exec_env[i] = ft_strdup(env[i]);
		if (!data->exec_env[i])
			fatal_error(data, "malloc");
		i++;
	}
}

void	load_username(t_gen_data *data)
{
	char	*symbol;
	char	*colored_username;
	char	*tmp;

	data->username = getenv("USER");
	if (!data->username)
	{
		ft_putendl_fd("minishell: couldn't create a username", 2);
		data->username = "minisheller";
	}
	colored_username = ft_strjoin(GREEN, data->username);
	if (!colored_username)
		fatal_error(data, "malloc");
	symbol = "> ";
	tmp = ft_strjoin(colored_username, symbol);
	if (!tmp)
		fatal_error(data, "malloc");
	free(colored_username);
	data->final_prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	if (!data->final_prompt)
		fatal_error(data, "malloc");
}
