/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:15 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/27 20:48:41 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_digit(char *args)
{
	int	i;
	int	digit;

	i = 0;
	digit = 1;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			digit = 0;
		i++;
	}
	return (digit);
}

void	exit_handler(t_gen_data *data, int exit_status)
{
	data->last_exit_status = exit_status;
	write_history(".user_history");
	free_data(data);
	free(data);
	data = NULL;
	printf("exit\n");
	usleep(500000);
	exit(exit_status);
}

void	exit_noargs(t_gen_data *data, char **args)
{
	int	last_exit;

	last_exit = data->last_exit_status;
	if (!args)
		exit_handler(data, last_exit);
	else
		return ;
}

void	exit_check(t_gen_data *data, char **args, int i)
{
	int	first_arg;

	first_arg = ft_atoi(args[1]);
	if (ft_atoi(args[1]) < 0)
		first_arg = ft_atoi(args[1]) * -1;
	if (i >= 2 && !is_digit(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		data->last_exit_status = 2;
		exit(data->last_exit_status);
	}
	if (i == 2 && first_arg >= 256)
		data->last_exit_status = first_arg % 256;
	if (i == 2 && first_arg < 256)
		data->last_exit_status = first_arg;
}

void	exit_fds(void)
{
	close(0);
	close(1);
	close(2);
}

int	exit_minishell(t_gen_data *data, char **args)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_fds();
	exit_noargs(data, args);
	while (args[i])
		i++;
	if (i > 2 && is_digit(args[1]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		data->last_exit_status = 1;
		return (1);
	}
	if (i >= 2)
	{
		exit_status = data->last_exit_status;
		exit_check(data, args, i);
		exit_handler(data, exit_status);
	}
	else
	{
		exit_status = data->last_exit_status;
		exit_handler(data, exit_status);
	}
	return (0);
}
