/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:30:24 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 17:03:28 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
Le philo doit prendre deux forchettes pour entrer dans la ft
1 fork --> les philos impair doir prende la fork
			gouche et le philo pair la fork droit
2 fork --> les philos impairs doivent prende la fork droit
			e les pairs fork gouche.

//--> si on precise pas quelle fork prendre rous les philo
		prennent una fork dans un certaine direction 
		ET ON CE retrouve dans un impasse ou il se demanderont mutuallm
		une forchette lorqu'ils prendront la deuxieme fork
*/
// int	lol_fork(int fork, t_info *philo);

int	take_fork(t_info *philo)
{
	int	fork;

	fork = 0;
	while (fork < 2)
	{
		if (check_stop_flag(philo))
		{
			if (fork == 1)
			{
				if (philo->id & 1)
					pthread_mutex_unlock
						(&philo->link_table->fork[philo->left_fork]);
				else
					pthread_mutex_unlock
						(&philo->link_table->fork[philo->right_fork]);
			}
			return (0);
		}
		if (even_fork(fork, philo) == 0)
			return (0);
		fork++;
	}
	return (1);
}

int	even_fork(int fork, t_info *philo)
{
	if (fork == 0)
	{
		if (philo->id & 1)
		{
			get_fork(philo, philo->left_fork);
			if (philo->link_table->philo_num == 1)
			{
				usleep(philo->link_table->time_to_die);
				pthread_mutex_unlock(&philo->link_table->fork[fork]);
				return (0);
			}
		}
		else
			get_fork(philo, philo->right_fork);
	}
	else if (fork == 1)
	{
		if (philo->id & 1)
			get_fork(philo, philo->right_fork);
		else
			get_fork(philo, philo->left_fork);
	}
	return (1);
}

void	get_fork(t_info *philo, int fork)
{
	pthread_mutex_lock(&philo->link_table->fork[fork]);
	mutex_printf("has taken a fork", philo, 2);
}

void	mutex_printf(char *string, t_info *philo, int color)
{
	if (check_stop_flag(philo))
		return ;
	pthread_mutex_lock(&philo->link_table->print);
	printf("%ld %d \033[0;3%dm%s\033[0m\n", get_time(philo->link_table->time),
		philo->id, color, string);
	pthread_mutex_unlock(&philo->link_table->print);
}

void	ft_monitoring_mutex(t_data *table)
{
	int	i;

	i = table->philo_num;
	while (1)
	{
		if (++i >= table->philo_num)
			i = 0;
		pthread_mutex_lock(&table->last_ate);
		if (get_time(table->link_philo[i]->last_eat) >= table->time_to_die)
		{
			if (table->link_philo[i]->eat_count != table->must_eat)
			{
				pthread_mutex_lock(&table->print);
				table->stop_flag = 1;
				printf("%ld %d died \n", get_time(table->time),
					table->link_philo[i]->id);
				pthread_mutex_unlock(&table->print);
			}
			pthread_mutex_unlock(&table->last_ate);
			break ;
		}
		pthread_mutex_unlock(&table->last_ate);
		usleep(300);
	}
}
