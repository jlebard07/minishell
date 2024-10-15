/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitfunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:25:28 by sperron           #+#    #+#             */
/*   Updated: 2024/10/15 12:50:03 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	waitfunction(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while(++i < data->nb_execs)
	{
		wait(&status);
		if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
	}
}