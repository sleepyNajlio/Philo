/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:00:51 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 17:26:22 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *ph, t_data *init, int i)
{
	init->start_time = ft_get_time();
	while (++i < init->num_of_philos)
	{	
		ph[i].id = i + 1;
		ph[i].last_eat = init->start_time;
		ph[i].meals_num = 0;
		pthread_mutex_init(&ph[i].fork, NULL);
		pthread_mutex_init(&ph[i].is_eating, NULL);
		ph[i].next_fork = &ph[(i + 1) % init->num_of_philos].fork;
		ph[i].data = init;
	}
}

void	args_mutex(char **av, t_data *init)
{
	init->num_of_philos = ft_atoi(av[1]);
	init->time_to_die = ft_atoi(av[2]);
	init->time_to_eat = ft_atoi(av[3]);
	init->time_to_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&init->print, NULL);
	pthread_mutex_init(&init->death_flag, NULL);
	pthread_mutex_init(&init->check_target, NULL);
}

int	data_init(int ac, char **av, t_data *init)
{
	if (ac == 5 || ac == 6)
	{
		args_mutex(av, init);
		init->is_dead = 1;
		init->e_target = 0;
		init->must_eat = -1;
		if (av[5])
		{
			init->must_eat = ft_atoi(av[5]);
			if (init->must_eat <= 0)
			{
				printf("problem in arguments");
				return (1);
			}
		}
		if (init->num_of_philos <= 0 || init->time_to_die <= 0 \
		|| init->time_to_eat <= 0 || init->time_to_sleep <= 0)
		{
			printf("problem in arguments");
			return (1);
		}
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char **av)
{
	t_data	*temp;
	t_philo	*ph;

	temp = malloc(sizeof(t_data));
	if (data_init(ac, av, temp))
		return (1);
	ph = malloc(sizeof(t_philo) * temp->num_of_philos);
	philo_init(ph, temp, -1);
	if (ft_create(ph, -1))
		return (1);
	ft_supervisor(ph);
	return (0);
}
