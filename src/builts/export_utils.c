/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:54:16 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 20:53:10 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_env_var(char **environ, char *var_name)
{
	int	i;
	int	name_len;

	if (!var_name)
		return (-1);
	i = 0;
	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, name_len) == 0
			&& environ[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_env_var_2(char **environ, char *var_name)
{
	int	i;
	int	name_len;

	if (!var_name)
		return (-1);
	i = 0;
	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**add_env_var(char **env, char *new_var)
{
	int		i;
	int		count;
	char	**new_env;

	count = 0;
	while (env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = ft_strdup(new_var);
	if (!new_env[count])
	{
		free_env(new_env);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	free_env(env);
	return (new_env);
}

int	check_valid_var_name(char *var)
{
	int	i;

	if (!var || !*var)
	{
		printf("minishell: export: '%s': not a valid identifier\n", var);
		return (1);
	}
	if (!((var[0] >= 'A' && var[0] <= 'Z') || (var[0] >= 'a' && var[0] <= 'z')
			|| var[0] == '_'))
	{
		printf("minishell: export: '%s': not a valid identifier\n", var);
		return (1);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!((var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && \
		var[i] <= 'z') || (var[i] >= '0' && var[i] <= '9') || var[i] == '_'))
		{
			printf("minishell: export: '%s': not a valid identifier\n", var);
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(char *env_var)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	if (has_equal(env_var) == 1)
	{
		while (env_var[i] != '\0')
		{
			if (i > 0 && env_var[i - 1] == '=')
				write(1, "\"", 1);
			write(1, &env_var[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	else
	{
		while (env_var[i] != '\0')
		{
			write(1, &env_var[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
