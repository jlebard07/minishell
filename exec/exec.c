/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/10/22 18:10:55 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redirect(t_data *data, t_execs *cmds, int (*pipe_fd)[2])
{
	bool	tab[2];
	
	tab[0] = (cmds->index == 1);
	tab[1] = (cmds->index == data->nb_execs);
	return (get_infile(data->in_fd, cmds, pipe_fd, tab), \
	get_outfile(data->out_fd, cmds, pipe_fd, tab));
}

void execute_cmds(t_data *data, t_execs *cmds, int (*pipe_fd)[2])
{
	int	status;

	status = 0;
	if (not_event(data->input) == 1)
		return (printf("bash: event not found\n"), \
		free_evolution(data), exit(0));
	get_redirect(data, cmds, pipe_fd);
	if (ft_strcmp(cmds->cmd, "cd") != 0 && \
	ft_strcmp(cmds->cmd, "history") != 0)
		status = is_builtin(data, data->out_fd, cmds);
	if (status != 128)
		return (free_evolution(data), exit(status));
	get_redirect(data, cmds, pipe_fd);
	ft_execvp(data, cmds);
	exit(status);
}

int pipeslines(t_data *data, t_execs **execs, int i)
{
	int		pipe_fd[data->nb_execs - 1][2];
	pid_t	pid;
	int		status;

	signal(SIGINT, ft_signal_in_exec);
	signal(SIGQUIT, ft_signal_in_exec);
	while (++i < data->nb_execs)
    {
        if (data->nb_execs - 1 > i)
            if (pipe(pipe_fd[i]) == -1)
                perror_exit("Error w/ a pipe\n", 2, data);
        if (check_builtins_env(find_x_node(*execs, i)))
			status = is_builtin(data, open("/dev/null", O_WRONLY), \
			find_x_node(*execs, i));
        pid = fork();
        if (pid == 0)
            execute_cmds(data, find_x_node(*execs, i), pipe_fd);
        else
        {
			if (i > 0)
				close(pipe_fd[i - 1][0]);
			if (i < data->nb_execs - 1)
				close(pipe_fd[i][1]);
        }
    }
    return (waitfunction(data), 0);
}
