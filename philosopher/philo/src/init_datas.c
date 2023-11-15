/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:08:47 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 14:24:35 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	parsing(int ac, char **av, t_data *table)
{
	table->must_eat = -1;
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_eat >= table->time_to_sleep)
	{
		if (table->philo_num % 2 == 0)
			table->time_to_think = table->time_to_eat - table->time_to_sleep;
		else
			table->time_to_think = (table->time_to_eat + table->time_to_eat)
				- table->time_to_sleep;
	}
	else
		table->time_to_think = 0;
	table->stop_flag = 0;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	table->time = get_time(0);
}

int	check_data(int ac, char **av, t_data *table)
{
	parsing(ac, av, table);
	if (table->philo_num < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (ac == 6 && table->must_eat < 1)
		|| ft_check_args(av) != 1)
		return (write(2, "Invalid Arguments\n", 19), 1);
	table->link_philo = malloc(sizeof(t_info) * table->philo_num);
	if (!table->link_philo)
		return (free(table->link_philo), 1);
	return (0);
}

void	init_philo(int i, t_info *philo, t_data *table)
{
	philo->id = i + 1;
	philo->left_fork = i;
	philo->right_fork = (i + 1) % table->philo_num;
	philo->link_table = table;
	philo->eat_count = 0;
	philo->last_eat = get_time(0);
}

int	init_mutex(t_data *table)
{
	int	i;

	i = -1;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->fork)
		return (free(table->fork), -2);
	while (++i < table->philo_num)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
		{
			while (i--)
				pthread_mutex_destroy(&table->fork[i]);
			return (-1);
		}
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (pthread_mutex_destroy(&table->print), -1);
	if (pthread_mutex_init(&table->last_ate, NULL))
		return (pthread_mutex_destroy(&table->last_ate), -1);
	return (0);
}

int	msleep(int time, t_info *philo)
{
	long	temp;

	temp = get_time(0);
	while (get_time(0) - temp + 9 < time)
	{
		usleep(9000);
		if (check_stop_flag(philo))
			return (0);
	}
	while (get_time(0) - temp < time)
	{
		usleep(1000);
		if (check_stop_flag(philo))
			return (0);
	}
	return (1);
}
