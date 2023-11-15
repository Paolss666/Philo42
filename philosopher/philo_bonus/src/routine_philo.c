/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:35:43 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/07 18:37:33 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	*check_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		sem_wait(philo->block_variable);
		if (find_time() - philo->t_meal > philo->t_die)
		{
			sem_post(philo->block_variable);
			stop_flag_died(philo);
			ft_post_all_sem(philo);
			return ((void *)0);
		}
		sem_post(philo->block_variable);
		sem_wait(philo->block_variable);
		if (philo->num_eat != -1 && !philo->num_eat)
			return (stop_flag_eat(philo), ft_post_all_sem(philo), (void *)0);
		sem_post(philo->block_variable);
		sem_wait(philo->block_eat);
		ft_print_check(philo);
		sem_post(philo->block_eat);
	}
	return ((void *)0);
}

void	ft_print_check(t_philo *philo)
{
	sem_wait(philo->block_variable);
	print_fork(philo);
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	print_fork2(philo);
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	print_eat(philo);
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	print_sleeping(philo);
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	print_think(philo);
	sem_post(philo->block_variable);
}

void	block_fork(t_philo *philo)
{
	sem_wait(philo->block_fork);
	sem_wait(philo->block_variable);
	philo->s_fork1 = 1;
	sem_post(philo->block_variable);
	sem_wait(philo->block_fork);
	sem_wait(philo->block_variable);
	philo->s_fork2 = 1;
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	philo->s_eat = 1;
	sem_post(philo->block_variable);
	sem_post(philo->block_fork);
	sem_post(philo->block_fork);
}

void	block_think_sleep(t_philo *philo)
{
	sem_wait(philo->block_variable);
	philo->num_eat--;
	sem_post(philo->block_variable);
	sem_post(philo->block_variable);
	sem_wait(philo->block_variable);
	philo->s_sleep = 1;
	sem_post(philo->block_variable);
	m_sleep(philo->t_sleep, philo);
	sem_wait(philo->block_variable);
	philo->s_think = 1;
	sem_post(philo->block_variable);
	m_sleep(philo->t_think, philo);
}

void	philo_start(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, NULL, check_monitor, philo))
		ft_error("Error => FAIL thread", NULL);
	if (philo->index % 2 == 0)
		usleep(500);
	while (1)
	{
		sem_wait(philo->block_variable);
		if (philo->died || philo->stop_flag)
			return ((void)0);
		sem_post(philo->block_variable);
		sem_wait(philo->block_sleep_think);
		block_fork(philo);
		sem_post(philo->block_sleep_think);
		m_sleep(philo->t_eat, philo);
		sem_wait(philo->block_variable);
		philo->t_meal = find_time();
		sem_post(philo->block_variable);
		sem_post(philo->block_sleep_think);
		block_think_sleep(philo);
		sem_wait(philo->block_sleep_think);
	}
}
