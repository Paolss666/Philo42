/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_pthread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:43:12 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 17:05:38 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_creat_thread(t_data *table, t_info **philo)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo[i] = malloc(sizeof(t_info));
		if (!philo[i])
			return (free(philo[i]), 1);
		init_philo(i, philo[i], table);
		table->link_philo[i] = philo[i];
		if ((pthread_create(&philo[i]->philosopher,
					NULL, &routine, (void *)philo[i])) != 0)
		{
			while (--i)
			{
				pthread_join(philo[i]->philosopher, NULL);
				free(philo[i]);
			}
			return (write(2, "Erreur FAIL pthread_create\n", 28), 1);
		}
	}
	return (0);
}

int	check_stop_flag(t_info *philo)
{
	pthread_mutex_lock(&philo->link_table->print);
	if (philo->link_table->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->link_table->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->link_table->print);
	return (0);
}

void	all_mutex_destroy(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->fork[i]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->last_ate);
}
