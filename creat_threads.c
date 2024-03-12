/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:52:52 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 15:42:52 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_thread_create(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philosophers_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("failed to create thread\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_inspector_thread(t_program *program)
{
	if (pthread_create(&program->inspector_thread, NULL, &philo_monitor,
			program->philos) != 0)
	{
		ft_putstr_fd("failed to create thread\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	join_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_of_philo)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			ft_putstr_fd("failed to join thread\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_inspector_thread(pthread_t inspector_thread)
{
	if (pthread_join(inspector_thread, NULL) != 0)
	{
		ft_putstr_fd("failed to join inspector thread\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}