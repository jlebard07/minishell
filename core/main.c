/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/16 12:37:56 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	core_loop(t_data *data)
{
	while (1)
	{
		set_input(data);
		if (ft_strncmp(data->input, "exit", 5) == 0)
			break ;
		if (data->input[0] != '\0')
		{
			parse_input(data);
		}
		else
		{
			free(data->input);
			continue ;			
		}
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
	if (!data.trash)
		perror_exit("Error w/ malloc.\n", 1);
	init_garbage_collector(data.trash);
	prepare_data(&data, env);
	set_cmd(&data);
	core_loop(&data);
	free_all(data.trash);
	return (0);
}
