/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:28:24 by sperron           #+#    #+#             */
/*   Updated: 2024/09/25 18:11:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_all_n(const char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


static void	write_argument(int fd, t_data *data, char *arg)
{
	char	*env_value;
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1])
		{
			write(fd, &arg[i + 1], 1);
			i += 2;
		}
		else if (arg[i] == '$')
		{
			j = i + 1;
			while (arg[j] && !ft_isspace(arg[j]) && arg[j] != '\'' \
			&& arg[j] != '\"')
				j++;
			var_name = ft_strndup(arg + i + 1, j - (i + 1));
			env_value = ft_getenv(data->env, var_name);
			free(var_name);
			if (env_value)
				write(fd, env_value, ft_strlen(env_value));
			i = j;
		}
		else
		{
			write(fd, &arg[i], 1);
			i++;
		}
	}
}

static void	write_args(int fd, t_data *data, char **args, int end)
{
	int		i;

	i = data->start;
	while (i < end)
	{
		if (args[i])
		{
			write_argument(fd, data, args[i]);
			if (i < end - 1)
				write(fd, " ", 1);
		}
		i++;
	}
}

int	handle_echo(t_data *data, char **args, int ac, int fd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (ac == 1)
	{
		write(fd, "\n", 1);
		return (0);
	}
	while ((i < ac && args[i][0] == '-' && args[i][1] == 'n' && \
	is_all_n(args[i])))
	{
		no_newline = 1;
		i++;
	}
	if (i == ac)
		return (0);
	data->start = i;
	write_args(fd, data, args, ac);
	if (!no_newline)
		write(fd, "\n", 1);
	return (0);
}
