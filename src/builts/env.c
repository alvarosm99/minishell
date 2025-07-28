/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:05 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 21:40:29 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **exec_env)
{
	int	i;

	i = 0;
	if (!exec_env)
		return (1);
	while (exec_env[i])
	{
		printf("%s\n", exec_env[i]);
		i++;
	}
	return (0);
}

void	free_env(char **exec_env)
{
	int	i;

	i = 0;
	if (exec_env)
	{
		while (exec_env[i])
		{
			if (exec_env[i])
				free(exec_env[i]);
			exec_env[i] = NULL;
			i++;
		}
		free(exec_env);
		exec_env = NULL;
	}
}
