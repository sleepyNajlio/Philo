/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:16:38 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 16:24:13 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				e_target;
	int				is_dead;
	long			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	check_target;
	pthread_mutex_t	death_flag;
}	t_data;

typedef struct s_philo
{
	pthread_t		philo;
	t_data			*data;
	int				id;
	long			last_eat;
	int				meals_num;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	is_eating;
}	t_philo;

long	ft_get_time(void);
int		ft_atoi(char *str);
int		ft_create(t_philo *ph, int i);
void	ft_supervisor(t_philo *ph);
void	ft_usleep(long time);
void	ft_print(t_philo *ph, char *str);

#endif