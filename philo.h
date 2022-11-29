/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 23:16:38 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 03:46:29 by nloutfi          ###   ########.fr       */
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

typedef struct s_all
{
	int				nb_p;
	int				tt_d;
	int				tt_e;
	int				tt_s;
	int				e_t;
	int				check;
	int				flag;
	long			simul;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	r_flag;
	pthread_mutex_t	printing;
}	t_all;

typedef int	t_index;

typedef struct s_philo
{
	pthread_t		philo;
	long			l_e;
	int				n_e;
	int				index;
	pthread_mutex_t	read_meals;
	pthread_mutex_t	fork;
	pthread_mutex_t	*nxt_fork;
	t_all			*all;
}	t_philo;

long	ft_get_time(void);
int		ft_atoi(char *str);
int		ft_creat(t_philo *philos, int i);
void	ft_supervisor(t_philo *philos);
void	ft_sleep(long time);
void	ft_print_philo(t_philo *philos, char *str);

#endif