/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 03:24:31 by nloutfi           #+#    #+#             */
/*   Updated: 2022/11/29 17:19:58 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time)
{
	long	time_to_reach;

	time_to_reach = ft_get_time() + time;
	usleep(time * 900);
	while (ft_get_time() < time_to_reach)
		usleep(25);
}

void	ft_print(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->data->print);
	printf("%ld %d %s\n", ft_get_time() - ph->data->start_time \
		, ph->id, str);
	pthread_mutex_unlock(&ph->data->print);
}

int	ft_num(char *str)
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
	if (ft_num(str))
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
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}
