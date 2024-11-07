/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:52:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/29 09:17:51 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_name_of(char *str, t_data *data)
{
	if (str[0] == '<' && (!str[1] || str[1] != '<'))
		return (err_rd("bash: syntax error near unexpected token `<'\n", \
		data));
	else if (str[0] == '<' && str[1] == '<' && (!str[2] || str[2] != '<'))
		return (err_rd("bash: syntax error near unexpected token `<<'\n", \
		data));
	else if (str[0] == '<')
		return (err_rd("bash: syntax error near unexpected token `<<<'\n", \
		data));
	else if (str[0] == '>' && (!str[1] || str[1] != '>'))
		return (err_rd("bash: syntax error near unexpected token `>'\n", \
		data));
	else if (str[0] == '>')
		return (err_rd("bash: syntax error near unexpected token `>>'\n", \
		data));
}

static bool	check_name_of(char **tab, t_data *data)
{
	int	i;

	i = -1;
	while (tab[0][++i] == '<' || tab[0][i] == '>')
		;
	if (tab[1])
	{
		if (tab[0][i] == 0 && (tab[1][0] == '<' || tab[1][0] == '>'))
			return (error_name_of(tab[1], data), false);
	}
	return (1);
}

int	redirect_bis(t_data *data, t_execs *exec, int i)
{
	if (check_name_of(exec->tokens + i, data) == 0)
		return (1);
	if (ctrl_redir_space(exec->tokens + i, data) == 0)
		return (1);
	if (exec->tokens[i][0] == '<')
		redirect_infile(data, exec, get_name_of(exec->tokens[i + 1], \
			data), (int)ft_strlen(exec->tokens[i]));
	else if (exec->tokens[i][0] == '>')
		redirect_outfile(exec, get_name_of(exec->tokens[i + 1], \
			data), data, (int)ft_strlen(exec->tokens[i]));
	return (0);
}