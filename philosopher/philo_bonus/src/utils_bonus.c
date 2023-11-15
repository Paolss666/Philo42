/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:55:31 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/07 18:24:50 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_error(char *s, t_philo *philo)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
	write(2, "\n", 1);
	if (!philo)
		exit(0);
	else
	{
		free(philo);
		exit(0);
	}
}

long long	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_check_args(char **av)
{
	int	i;
	int	k;

	i = 0;
	while (av[++i])
	{
		k = -1;
		while (av[i][++k])
			if (!(av[i][k] >= '0' && av[i][k] <= '9'))
				return (0);
	}
	return (1);
}

void	m_sleep(long long time, t_philo *philo)
{
	long long	t;

	t = find_time();
	while (!(find_time() - t >= time))
	{
		sem_wait(philo->block_time);
		if (philo->stop_flag)
		{
			sem_post(philo->block_time);
			break ;
		}
		sem_post(philo->block_time);
		usleep(500);
	}
}

void	philo_printf(t_philo *philo, char *str)
{
	sem_wait(philo->block_printf);
	if (!philo->stop_flag)
		printf("%lld %d %s\n", find_time() - philo->t_start, philo->index, str);
	sem_post(philo->block_printf);
}
