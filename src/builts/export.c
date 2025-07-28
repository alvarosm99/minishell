/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:23 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 21:36:20 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**update_env_handler(char **new_env, char **old_env, int size, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
    {
        if (j == flag)
        {
            j++;
            continue;
        }
        new_env[i] = ft_strdup(old_env[j]);
        if (!new_env[i])
        {
            free_env(new_env);
            return (NULL);
        }
        i++;
        j++;
    }
	new_env[i] = NULL;
	return (new_env);
}

char **update_env(char **old_env, int size, int flag)
{
	int		i;
    char	**new_env;

	i = 0;
    new_env = malloc(sizeof(char *) * size);
    if (!new_env)
	{
    	return (NULL);
	}
	while (i < size)
	{
		new_env[i] = NULL;
		i++;
	}
	new_env = update_env_handler(new_env, old_env, size, flag);
    free_env(old_env);
    return (new_env);
}

int	export(t_gen_data *data, char **executables, char **exec_env)
{
	int	i;
	int	valid;
	int	invalid;
	
	i = 1;
	if (!executables[i])
	{
		export_empty_args(data, exec_env);
		return (data->last_exit_status);
	}
	valid = 0;
	invalid = 0;
	while (executables[i])
	{
		if (ft_strchr(executables[i], '='))
		{
			if (!check_valid_var_name(executables[i]))
			{
				export_var_env(data, executables[i]);
				export_var_exp1(data, executables[i]);
				valid = 1;
			}
			else
				invalid = 1;
		}
		else
		{
			if (!check_valid_var_name(executables[i]))
			{
				export_var_exp2(data, executables[i]);
				valid = 1;
			}
			else
				invalid = 1;
		}
			i++;
	}
	drop_duplicated(data);
	export_exit_status(data, valid, invalid);
	return (data->last_exit_status);
}
