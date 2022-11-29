/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:00:51 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 03:06:06 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_philo *philos, t_all *init, int i)
{
	init->simul = ft_get_time();
	while (++i < init->nb_p)
	{	
		philos[i].index = i + 1;
		philos[i].l_e = init->simul;
		philos[i].n_e = 0;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].read_meals, NULL);
		philos[i].nxt_fork = &philos[(i + 1) % init->nb_p].fork;
		philos[i].all = init;
	}
}

int	ft_init_data(int argc, char **argv, t_all *init)
{
	if (argc == 5 || argc == 6)
	{
		init->nb_p = ft_atoi(argv[1]);
		init->tt_d = ft_atoi(argv[2]);
		init->tt_e = ft_atoi(argv[3]);
		init->tt_s = ft_atoi(argv[4]);
		init->flag = 1;
		init->check = 0;
		init->e_t = -1;
		if (argv[5])
		{
			init->e_t = ft_atoi(argv[5]);
			if (init->e_t <= 0)
			{
				printf("prob in arg");
				return (1);
			}
		}
		if (init->nb_p <= 0 || init->tt_d <= 0 || init->tt_e <= 0 \
			|| init->tt_s <= 0)
		{
			printf("prob in arg");
			return (1);
		}
		pthread_mutex_init(&init->printing, NULL);
		pthread_mutex_init(&init->r_flag, NULL);
		pthread_mutex_init(&init->check_eat, NULL);
		return (0);
	}
	else
		return (1);
}

int	main(int argc, char **argv)
{
	t_all	*init;
	t_philo	*philos;

	init = malloc(sizeof(t_all));
	if (ft_init_data(argc, argv, init))
		return (1);
	philos = malloc(sizeof(t_philo) * init->nb_p);
	ft_init_philo(philos, init, -1);
	if (ft_creat(philos, -1))
		return (1);
	ft_supervisor(philos);
	return (0);
}