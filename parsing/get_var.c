/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/11/04 11:40:55 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_backslashes_pos(char *str, int pos)
{
	int	count;

	count = 0;
	while (pos > 0 && str[--pos] == '\\')
		count++;
	return (count);
}

char	*check_exit_code(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?' && !is_in_quotes(token, i))
		{
			token = handle_exit_code(token, i, data);
			break ;
		}
		i++;
	}
	return (token);
}

int	count_exit_code(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

char	*process_replace(t_data *data, int i, int j, char *str)
{
	char	*dollar_value;
	char	*env_value;

	dollar_value = ft_substr(str, i + 1, j - 1);
	if (!ft_strchr(dollar_value, '?'))
	{
		env_value = get_var_in_env(data->env, dollar_value, data);
		str = replace_in_str(data, str, env_value, i);
	}
	else
		str = check_exit_code(str, data);
	free(dollar_value);
	if (str[0] != '\0')
		add_ptr(data->trash, str);
	return (str);
}

char	*replace_var(char *str, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	str = get_var_number(data, str);
	while (str[++i])
	{
		if (big_conditions(str, i) == true)
		{
			j = 1;
			if (str[i + 1] != '?')
				while (is_valid_character(str[i + j]))
					j++;
			else
				j++;
			str = process_replace(data, i, j, str);
			i = -1;
		}
		else if (str[i] == '$')
			continue ;
	}
	return (str = process_backslashes(data, str), str);
}
