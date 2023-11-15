/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:57:19 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 14:38:18 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	eating(t_info *philo)
{
	int	result;

	result = 1;
	if (check_stop_flag(philo))
	{
		pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->link_table->print);
	printf("%ld %d is eating\n", get_time(philo->link_table->time), philo->id);
	pthread_mutex_unlock(&philo->link_table->print);
	pthread_mutex_lock(&philo->link_table->last_ate);
	philo->last_eat = get_time(0);
	philo->eat_count++;
	if (philo->eat_count == philo->link_table->must_eat)
		result = 0;
	pthread_mutex_unlock(&philo->link_table->last_ate);
	msleep(philo->link_table->time_to_eat, philo);
	pthread_mutex_unlock(&philo->link_table->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->link_table->fork[philo->right_fork]);
	return (result);
}

int	sleeping(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is sleeping", philo, 5);
	msleep(philo->link_table->time_to_sleep, philo);
	return (1);
}

int	thinking(t_info *philo)
{
	if (check_stop_flag(philo))
		return (0);
	mutex_printf("is thinking", philo, 6);
	msleep(philo->link_table->time_to_think, philo);
	return (1);
}
