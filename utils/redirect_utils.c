/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:19:54 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/07 11:11:53 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ctrl_redir_space(char **tab, t_data *data)
{
	if (!tab[1] || tab[1][0] == 0)
	{
		data->error = true;
		return (err_rd \
		("bash: syntax error near unexpected token `newline'\n", data), 0);
	}
	return (1);
}

void	err_rd(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	data->error = true;
}

bool	checker_redirect_in(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == '<')
		;
	if (i == 0)
		return (false);
	if (i == 4)
		return (err_rd("bash: syntax error near unexpected token `<'\n", \
		data), (false));
	else if (i == 5)
		return (err_rd("bash: syntax error near unexpected token `<<'\n", \
		data), (false));
	else if (i > 5)
		return (err_rd("bash: syntax error near unexpected token `<<<'\n", \
		data), (false));
	else if (str[i] == '>' && str[i + 1] == '>' && i != 0)
		return (err_rd("bash: syntax error near unexpected token `>>'\n", \
		data), (false));
	else if (str[i] == '>' && i != 0)
		return (err_rd("bash: syntax error near unexpected token `>'\n", \
		data), (false));
	return (true);
}

bool	checker_redirect_out(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == '>')
		;
	if (i == 0)
		return (false);
	if (i == 3)
		return (err_rd("bash: syntax error near unexpected token `>'\n", \
		data), (false));
	else if (i > 3)
		return (err_rd("bash: syntax error near unexpected token `>>'\n", \
		data), (false));
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<' && i != 0)
		return (err_rd("bash: syntax error near unexpected token `<<<'\n", \
		data), (false));
	else if (str[i] == '<' && str[i + 1] == '<' && i != 0)
		return (err_rd("bash: syntax error near unexpected token `<<'\n", \
		data), (false));
	else if (str[i] == '<' && i != 0)
		return (err_rd("bash: syntax error near unexpected token `<'\n", \
		data), (false));
	return (true);
}
