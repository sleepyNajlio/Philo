/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:46:24 by yobenali          #+#    #+#             */
/*   Updated: 2022/11/29 02:17:23 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_digit(char *str)
{
	int	i;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	char	digit;
	int		res;
	int		max;
	int		i;

	res = 0;
	i = 0;
	max = INT_MAX / 10;
	if (is_digit(str))
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (res > max || (res == max && digit > 7))
			return (0);
		res = res * 10 + digit;
		i++;
	}
	return (res);
}

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

void	ft_print_philo(t_philo *philos, char *str)
{
	pthread_mutex_lock(&philos->all->printing);
	printf("%ld %d %s\n", ft_get_time() - philos->all->simul \
		, philos->index, str);
	pthread_mutex_unlock(&philos->all->printing);
}

void	ft_sleep(long time)
{
	long	time_to_reach;

	time_to_reach = ft_get_time() + time;
	usleep(time * 900);
	while (ft_get_time() < time_to_reach)
		usleep(25);
}
