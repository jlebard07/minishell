/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:04:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 12:26:24 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	perror_exit(char *str, int exit_code)
{
	ft_putendl_fd(str, 2);
	exit(exit_code);
}
