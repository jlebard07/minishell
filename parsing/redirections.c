/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:52:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 16:56:31 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redirect_infile(t_data *data, t_execs *exec, char *name_of,
				int count)
{
	char	*err_msg;

	if (count == 1)
	{
		if (access(name_of, F_OK) == -1)
		{
			err_msg = ft_strjoin("bash: ", name_of);
			err_msg = ft_strjoin_free_s1(err_msg, \
			": No such file or directory\n");
			err_rd(err_msg, data);
			return (free(err_msg), 0);
		}
		exec->infile = name_of;
		return ((int)ft_strlen(name_of) + count - 1);
	}
	else if (count >= 2)
		return (handle_heredoc(data, exec, name_of, count));
	return (0);
}

static int	redirect_outfile(t_execs *exec, char	*name_of,
					int count)
{
	if (count == 1)
	{
		exec->tronque = 1;
		open(name_of, O_CREAT, O_EXCL);
		exec->outfile = name_of;
	}
	else if (count == 2)
	{
		open(name_of, O_CREAT, O_EXCL);
		exec->outfile = name_of;
	}
	return ((int)ft_strlen(name_of) + count - 1);
}

static char	*get_name_of(char *str, t_data *data)
{
	int		i;
	char	*name_of;

	i = -1;
	while (str[++i] && str[i] != '<' && str[i] != '>')
		;
	name_of = ft_strndup(str, i);
	add_ptr(data->trash, name_of);
	return (name_of);
}

static void	get_all_redir_in_str(t_data *data, t_execs *exec, char *str)
{
	int		i;
	int		j;
	char	*name_of;

	i = -1;
	j = 0;
	while (data->error == false && str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (checker_redirect_in(str + i, data) == 0 && \
				checker_redirect_out(str + i, data) == 0)
				return ;
			while (str[i + ++j] == str[i])
				;
			name_of = get_name_of(str + i + j, data);
			if (str[i] == '<')
				i += redirect_infile(data, exec, name_of, j);
			else
				i += redirect_outfile(exec, name_of, j);
			j = 0;
		}
	}
}

int	redirect(t_data *data, t_execs *exec)
{
	int	i;

	i = -1;
	while (data->error == false && exec->tokens[++i])
	{
		if (redirs_in_str(exec->tokens[i]) == 1)
		{
			if (last_chara(exec->tokens[i]) == 1)
				return (err_rd \
				("bash: syntax error near unexpected token `newline'\n", \
				data), 1);
			get_all_redir_in_str(data, exec, exec->tokens[i]);
		}
		else if (checker_redirect_in(exec->tokens[i], data) == 1 || \
			checker_redirect_out(exec->tokens[i], data) == 1)
		{
			if (ctrl_redir_space(exec->tokens + i, data) == 0)
				return (1);
			if (exec->tokens[i][0] == '<')
				redirect_infile(data, exec, get_name_of(exec->tokens[i + 1], \
					data), (int)ft_strlen(exec->tokens[i]));
			else if (exec->tokens[i][0] == '>')
				redirect_outfile(exec, get_name_of(exec->tokens[i + 1], \
					data), (int)ft_strlen(exec->tokens[i]));
		}
	}
	return (0);
}
