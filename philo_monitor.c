/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:47:55 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 12:25:25 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	size_t	die_time;

	pthread_mutex_lock(philo->meal_mutex);
	die_time = get_current_time() - philo->last_meal;
	if (time > philo->data->time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

int	check_if_philosopher_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_of_philo)
	{
		if (is_philo_dead(&philos[i]))
		{
			print_message("died", &philos[i]);
			pthread_mutex_lock(philos->death_mutex);
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_philosophers_eaten(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->data->num_times_to_eat == -1)
		return (0);
	while (i < philos->data->nb_of_philo)
	{
		pthread_mutex_lock(philos->meal_mutex);
		if (philos[i].eaten_meal < philos->data->num_times_to_eat)
		{
			pthread_mutex_unlock(philos->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(philos->meal_mutex);
		i++;
	}
	pthread_mutex_lock(philos->death_mutex);
	*philos->dead_flag = 1;
	pthread_mutex_unlock(philos->death_mutex);
	return (1);
}

void	*monitor_philo(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_if_philosophers_dead(philos)
			|| check_all_philosophers_eaten(philos))
			break ;
	}
	return (arg);
}