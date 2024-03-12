/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mange_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:07:22 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 15:10:54 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->data.nb_of_philo)
	{
		if (pthread_mutex_destroy(&program->forks[i]) != 0)
		{
			ft_putstr_fd("failed to destroy mutex\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&program->death_mutex) != 0
		|| pthread_mutex_destroy(&program->meal_mutex) != 0
		|| pthread_mutex_destroy(&program->result_mutex) != 0)
	{
		ft_putstr_fd("failed to destroy mutex\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}