/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:29:24 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 03:30:54 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
