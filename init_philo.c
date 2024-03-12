/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:52:12 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 11:18:21 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_putstr_fd("Failed to initialize mutex\n",
				STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philos(t_program *program)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_data		*data;

	i = 0;
	philos = program->philos;
	forks = program->forks;
	data = &program->data;
	while (i < data->nb_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].is_eating = 0;
		philos[i].eaten_meal = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->nb_of_philo];
		philos[i].dead_flag = &program->dead_flag;
		philos[i].death_mutex = &program->death_mutex;
		philos[i].meal_mutex = &program->meal_mutex;
		philos[i].result_mutex = &program->result_mutex;
		i++;
	}
}

int	init_program(t_program *program)
{
	if (init_forks(program->forks, program->data.nb_of_philo) != 0)
		return (1);
	program->dead_flag = 0;
	if (pthread_mutex_init(&program->death_mutex, NULL) != 0
		|| pthread_mutex_init(&program->meal_mutex, NULL) != 0
		|| pthread_mutex_init(&program->result_mutex, NULL) != 0)
	{
		ft_putstr_fd("Failed to initialize mutex\n", STDERR_FILENO);
		return (1);
	}
	init_philosophers(program);
	return (0);
}