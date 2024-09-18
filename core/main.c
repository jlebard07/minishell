/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/18 11:00:57 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_history(t_history *history)
{
	size_t	i;

	i = -1;
	while (i < history->count)
		free(history->save[i++]);
	free(history);
}

void	core_loop(t_data *data, char **env)
{
	while (1)
	{
		set_input(data, env);
		if (ft_strncmp(data->input, "exit", 5) == 0)
		{
			free_all(data->trash);
			free_history(data->history);
			break ;
		}
		if (data->input[0] != '\0')
			parse_input(data);
		free_all(data->trash);
	}
}

int	array_len(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.trash = malloc(sizeof(t_garb_c));
	data.history = NULL;
	if (!data.trash)
		perror_exit("Error w/ malloc.\n", 1);
	init_garbage_collector(data.trash);
	set_cmd(&data);
	core_loop(&data, env);
	free_all(data.trash);
	return (0);
}
