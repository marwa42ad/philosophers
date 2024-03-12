/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:41:55 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 11:44:14 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    think_action(t_philo *philo)
{
    print_message(philo, "is thinking");
}

void    sleep_action(t_philo *philo)
{
    print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->data->nb_of_philo == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->is_eating = 1;
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time();
	philo->eaten_meal++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat);
	while (is_philosopher_alive(philo))
	{
		eat_action(philo);
        sleep_action(philo);
        think_action(philo);
		if (philo->data->nb_of_philo == 1)
			break ;
	}
	return (arg);
}