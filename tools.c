/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:44:48 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 17:19:36 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->death_flag);
	if (ph->data->is_dead == 0)
	{
		pthread_mutex_unlock(&ph->data->death_flag);
		return (0);
	}
	pthread_mutex_unlock(&ph->data->death_flag);
	return (1);
}

void	ft_must_eat(t_philo *ph)
{
	if (ph->meals_num == ph->data->must_eat && ph->data->must_eat != -1)
	{
		pthread_mutex_lock(&ph->data->check_target);
		ph->data->e_target++;
		pthread_mutex_unlock(&ph->data->check_target);
	}
}

void	ft_eat(t_philo *ph)
{
	ft_print(ph, "is eating");
	pthread_mutex_lock(&ph->is_eating);
	ph->last_eat = ft_get_time();
	pthread_mutex_unlock(&ph->is_eating);
	ft_usleep(ph->data->time_to_eat);
}

void	*ph_routine(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	if (ph->id % 2 == 0)
		ft_usleep(ph->data->time_to_eat / 10);
	while (is_dead(ph))
	{
		pthread_mutex_lock(&ph->fork);
		ft_print(ph, "has taken a fork");
		pthread_mutex_lock(ph->next_fork);
		ft_print(ph, "has taken a fork");
		pthread_mutex_lock(&ph->is_eating);
		ph->meals_num++;
		ft_must_eat(ph);
		pthread_mutex_unlock(&ph->is_eating);
		pthread_mutex_unlock(ph->next_fork);
		pthread_mutex_unlock(&ph->fork);
		ft_print(ph, "is sleeping");
		ft_usleep(ph->data->time_to_sleep);
		ft_print(ph, "is thinking");
	}
	return (0);
}

int	ft_create(t_philo *ph, int i)
{
	while (++i < ph->data->num_of_philos)
	{
		if (pthread_create(&ph[i].philo, NULL, ph_routine, &ph[i]) != 0)
			return (1);
		if (pthread_detach(ph[i].philo) != 0)
			return (1);
	}
	return (0);
}
