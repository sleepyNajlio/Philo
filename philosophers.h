/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:50:36 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/29 02:16:23 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef int	t_index;

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

int		ft_atoi(char *str);
int		ft_check_flag(t_philo *philos);
int		ft_creat(t_philo *philos, int i);
int		ft_check_meals(t_philo *philos, t_index i);
long	ft_get_time(void);
void	*routine(void *p);
void	ft_sleep(long time);
void	ft_supervisor(t_philo *philos);
void	ft_print_philo(t_philo *philos, char *str);

#endif