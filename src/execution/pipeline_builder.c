/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:41:02 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/28 12:24:06 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_fill(t_gen_data *data, t_redirector **redirections, int i_start)
{
	int		i;
	char	*target;

	i = 0;
	while (data->executables[i_start] 
		&& data->executables[i_start]->type != PIPE)
	{
		if (data->executables[i_start]->type == REDIRECTOR)
		{
			target = data->executables[i_start + 1]->text;
			redirections[i] = malloc(sizeof(t_redirector));
			if (!ft_strcmp(data->executables[i_start]->text, "<"))
				redirections[i]->type = INPUT;
			else if (!ft_strcmp(data->executables[i_start]->text, "<<"))
				redirections[i]->type = HEREDOC;
			else if (!ft_strcmp(data->executables[i_start]->text, ">"))
				redirections[i]->type = OUTPUT;
			else if (!ft_strcmp(data->executables[i_start]->text, ">>"))
				redirections[i]->type = APPEND;
			redirections[i]->target_file = ft_strdup(target);
			if (!redirections[i]->target_file)
				fatal_error(data, "malloc");
			i++;
		}
		i_start++;
	}
}

void	redir_assign(t_command *command, t_gen_data *data, int index)
{
	t_redirector **redirections;
	int			size;
	int			i_start;
	
	size = 0;
	while (index > 0 && data->executables[index]->type != PIPE)
		index--;
	if (index > 0 && data->executables[index]->type == PIPE)
		index++;
	i_start = index;
	while (data->executables[index] && data->executables[index]->type != PIPE)
	{
		if (data->executables[index]->type == REDIRECTOR)
			size++;
		index++;
	}
	redirections = malloc(sizeof(t_redirector *) * (size + 1));
	if (!redirections)
		fatal_error(data, "malloc");
	redirections[size] = NULL;
	redir_fill(data, redirections, i_start);
	command->redirections = redirections;
}

void	argv_fill(t_command *command, t_gen_data *data, int index)
{
	int	size;
	int	cmd_pos;
	int	i;
	
	size = 1;
	cmd_pos = index;
	index++;
	while (data->executables[index] && data->executables[index]->type == ARG)
	{
		size++;
		index++;
	}
	index = cmd_pos;
	command->argv = malloc(sizeof(char *) * (size + 1));
	if (!command->argv)
		fatal_error(data, "malloc");
	command->argv[size] = NULL;
	i = 0;
	command->argv[i++] = ft_strdup(data->executables[cmd_pos++]->text);
	while (data->executables[cmd_pos] && data->executables[cmd_pos]->type == ARG)
		command->argv[i++] = ft_strdup(data->executables[cmd_pos++]->text);
	redir_assign(command, data, index);
}

t_command	*command_fill(t_gen_data *data, int index)
{
	t_command *command;
	
	command = malloc(sizeof(t_command));
	if (!command)
		fatal_error(data, "malloc");
	argv_fill(command, data, index);
	return (command);
}

t_command	**command_array_builder(
	t_command **command_array, t_gen_data *data, int size)
{
	int	i;
	int	j;
	
	if (size == 0)
	{
		command_array = ft_calloc(sizeof(t_command *), 2);
		command_array[0] = malloc(sizeof(t_command));
		command_array[0]->argv = NULL;
		redir_assign(command_array[0], data, 0);
		return (command_array);
	}
	command_array = ft_calloc(sizeof(t_command *), (size + 1));
	if (!command_array)
		fatal_error(data, "malloc");
	i = 0;
	j = 0;
	while (data->executables[i])
	{
		if (data->executables[i]->type == COMMAND)
			command_array[j++] = command_fill(data, i);
		i++;
	}
	return (command_array);
}
