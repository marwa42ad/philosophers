/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:04:17 by marwamostaf       #+#    #+#             */
/*   Updated: 2023/12/09 18:18:59 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_content_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
		{
			ft_putstr_fd(" Erorr: Invalid Number\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_validat_args(t_data *data)
{
	if (data->nb_of_philo > 200)
	{
		ft_putstr_fd("Error: Invalid Number of philosophers\n", STDERR_FILENO);
		return (1);
	}
	if (data->time_to_die < 60)
	{
		ft_putstr_fd("Error: Time to die is Invalid\n",
			STDERR_FILENO);
		return (1);
	}
	if (data->time_to_eat < 60)
	{
		ft_putstr_fd("Error: Time to eat is Invalid\n",
			STDERR_FILENO);
		return (1);
	}
	if (data->time_to_sleep < 60)
	{
		ft_putstr_fd("Error: Time to sleep is Invalid\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_command_line(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: Invalid Number of Argument\n", STDERR_FILENO);
		return (1);
	}
	if (!check_content_args(argc, argv))
		return (1);
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	if (check_validate_args(data) != 0)
		return (1);
	return (0);
}