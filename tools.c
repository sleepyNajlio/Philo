/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:44:48 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 03:23:26 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

int	ft_check_flag(t_philo *philos)
{
	pthread_mutex_lock(&philos->all->r_flag);
	if (philos->all->flag == 0)
	{
		pthread_mutex_unlock(&philos->all->r_flag);
		return (0);
	}
	pthread_mutex_unlock(&philos->all->r_flag);
	return (1);
}

void	ft_must_eat(t_philo *philos)
{
	if (philos->n_e == philos->all->e_t && philos->all->e_t != -1)
	{
		pthread_mutex_lock(&philos->all->check_eat);
		philos->all->check++;
		pthread_mutex_unlock(&philos->all->check_eat);
	}
}

void	*routine(void *p)
{
	t_philo	*philos;

	philos = (t_philo *)p;
	if (philos->index % 2 == 0)
		ft_sleep(philos->all->tt_e / 10);
	while (ft_check_flag(philos))
	{
		pthread_mutex_lock(&philos->fork);
		ft_print_philo(philos, "has taken a fork");
		pthread_mutex_lock(philos->nxt_fork);
		ft_print_philo(philos, "has taken a fork");
		ft_print_philo(philos, "is eating");
		pthread_mutex_lock(&philos->read_meals);
		philos->l_e = ft_get_time();
		pthread_mutex_unlock(&philos->read_meals);
		ft_sleep(philos->all->tt_e);
		pthread_mutex_lock(&philos->read_meals);
		philos->n_e++;
		ft_must_eat(philos);
		pthread_mutex_unlock(&philos->read_meals);
		pthread_mutex_unlock(philos->nxt_fork);
		pthread_mutex_unlock(&philos->fork);
		ft_print_philo(philos, "is sleeping");
		ft_sleep(philos->all->tt_s);
		ft_print_philo(philos, "is thinking");
	}
	return (0);
}

int	ft_creat(t_philo *philos, int i)
{
	while (++i < philos->all->nb_p)
	{
		if (pthread_create(&philos[i].philo, NULL, routine, &philos[i]) != 0)
			return (1);
		if (pthread_detach(philos[i].philo) != 0)
			return (1);
	}
	return (0);
}
