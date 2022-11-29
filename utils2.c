/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:54:31 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/29 02:15:55 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	ft_check_meals(t_philo *philos, t_index i)
{
	pthread_mutex_lock(&philos[i].all->check_eat);
	if (philos->all->check == philos->all->nb_p)
	{
		pthread_mutex_lock(&philos->all->r_flag);
		philos->all->flag = 0;
		pthread_mutex_unlock(&philos->all->r_flag);
		return (1);
	}
	pthread_mutex_unlock(&philos[i].all->check_eat);
	return (0);
}

int	ft_ch_flag(t_philo *philos, t_index i)
{
	if (ft_get_time() - philos[i].l_e >= philos[i].all->tt_d)
	{
		pthread_mutex_lock(&philos->all->r_flag);
		philos->all->flag = 0;
		pthread_mutex_unlock(&philos->all->r_flag);
		printf("%ld %d died\n", ft_get_time() - philos->all->simul, \
			philos->index);
		return (1);
	}
	return (0);
}

void	ft_supervisor(t_philo *philos)
{
	t_index	i;

	while (1)
	{
		i = 0;
		while (i < philos->all->nb_p)
		{
			pthread_mutex_lock(&philos->all->printing);
			if (philos->all->e_t != -1 \
				&& ft_check_meals(philos, i) == EXIT_FAILURE)
				return ;
			pthread_mutex_lock(&philos[i].read_meals);
			if (ft_ch_flag(philos, i) == EXIT_FAILURE)
				return ;
			pthread_mutex_unlock(&philos->all->printing);
			pthread_mutex_unlock(&philos[i].read_meals);
			i++;
		}
		usleep(50);
	}
}
