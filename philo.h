/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:52:33 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/10 11:17:53 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_NUM_PHILOSOPHERS 200

typedef struct data
{
	int				nb_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_data		    *data;

	int				is_eating;
	int				eaten_meal;
	size_t			last_meal;
	size_t			start_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				*dead_flag;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*result_mutex;
}					t_philo;

typedef struct s_program
{
	t_data		data;
	pthread_t		inspector_thread;
	t_philo			philos[MAX_NUM_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_NUM_PHILOSOPHERS];

	int				dead_flag;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	result_mutex;
}					t_program;

int					is_numeric(const char *str);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);

#endif /* PHILO_H */