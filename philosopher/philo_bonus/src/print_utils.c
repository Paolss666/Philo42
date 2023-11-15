/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:33:05 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/08 14:17:55 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_fork(t_philo *philo)
{
	if (philo->s_fork1)
	{
		sem_post(philo->block_variable);
		philo_printf(philo, "has taken a fork");
		sem_wait(philo->block_variable);
		philo->s_fork1 = 0;
	}
	sem_post(philo->block_variable);
}

void	print_fork2(t_philo *philo)
{
	if (philo->s_fork2)
	{
		sem_post(philo->block_variable);
		philo_printf(philo, "has taken a fork");
		sem_wait(philo->block_variable);
		philo->s_fork2 = 0;
	}
	sem_post(philo->block_variable);
	return ;
}

void	print_eat(t_philo *philo)
{
	if (philo->s_eat)
	{
		sem_post(philo->block_variable);
		philo_printf(philo, "is eating");
		sem_wait(philo->block_variable);
		philo->s_eat = 0;
	}
	sem_post(philo->block_variable);
	return ;
}

void	print_sleeping(t_philo *philo)
{
	if (philo->s_sleep)
	{
		sem_post(philo->block_variable);
		philo_printf(philo, "is sleeping");
		sem_wait(philo->block_variable);
		philo->s_sleep = 0;
	}
	sem_post(philo->block_variable);
	return ;
}

void	print_think(t_philo *philo)
{
	if (philo->s_think)
	{
		sem_post(philo->block_variable);
		philo_printf(philo, "is thinking");
		sem_wait(philo->block_variable);
		philo->s_think = 0;
	}
	sem_post(philo->block_variable);
	return ;
}
