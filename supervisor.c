/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:29:24 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 17:08:24 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph[i].data->check_target);
	if (ph->data->e_target == ph->data->num_of_philos)
	{
		pthread_mutex_lock(&ph->data->death_flag);
		ph->data->is_dead = 0;
		pthread_mutex_unlock(&ph->data->death_flag);
		return (1);
	}
	pthread_mutex_unlock(&ph[i].data->check_target);
	return (0);
}

int	check_death(t_philo *ph, int i)
{
	if (ft_get_time() - ph[i].last_eat >= ph[i].data->time_to_die)
	{
		pthread_mutex_lock(&ph->data->death_flag);
		ph->data->is_dead = 0;
		pthread_mutex_unlock(&ph->data->death_flag);
		printf("%ld %d died\n", ft_get_time() - ph->data->start_time, \
			ph->id);
		return (1);
	}
	return (0);
}

void	ft_supervisor(t_philo *ph)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ph->data->num_of_philos)
		{
			pthread_mutex_lock(&ph->data->print);
			if (ph->data->must_eat != -1 \
				&& check_meals(ph, i))
				return ;
			pthread_mutex_lock(&ph[i].is_eating);
			if (check_death(ph, i))
				return ;
			pthread_mutex_unlock(&ph->data->print);
			pthread_mutex_unlock(&ph[i].is_eating);
			i++;
		}
		usleep(50);
	}
}
