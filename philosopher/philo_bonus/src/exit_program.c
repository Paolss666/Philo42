/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:39:34 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/07 18:27:36 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	stop_flag_eat(t_philo *philo)
{
	sem_wait(philo->block_time);
	philo->stop_flag = 1;
	sem_post(philo->block_variable);
}

void	stop_flag_died(t_philo *philo)
{
	sem_wait(philo->block_variable);
	philo->died = 1;
	sem_post(philo->block_variable);
	sem_wait(philo->block_printf);
	printf("%lld %d %s\n", \
			find_time() - philo->t_start, philo->index, "died");
	sem_wait(philo->block_time);
	philo->stop_flag = 1;
	sem_post(philo->block_variable);
}

void	ft_post_all_sem(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < 2 * philo->num_philos)
	{
		sem_post(philo->block_variable);
		sem_post(philo->block_fork);
		sem_post(philo->block_time);
		sem_post(philo->block_eat);
	}
}

void	exit_philo(t_philo **philo)
{
	t_philo	*tmp;
	int		i;
	int		status;

	tmp = *philo;
	i = -1;
	while (++i < tmp->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < tmp->num_philos)
				kill(tmp->pid[i], SIGKILL);
			break ;
		}
	}
	ft_post_all_sem(tmp);
	exit_philo_2(tmp);
}

void	exit_philo_2(t_philo *philo)
{
	sem_close(philo->block_printf);
	sem_unlink("/block_print");
	sem_close(philo->block_fork);
	sem_unlink("/block_fork");
	sem_close(philo->block_variable);
	sem_unlink("/block_variable");
	sem_close(philo->block_time);
	sem_unlink("/block_time");
	sem_close(philo->block_eat);
	sem_unlink("/block_eat");
	sem_close(philo->block_sleep_think);
	sem_unlink("/block_sleep_think");
	free(philo->pid);
	free(philo);
	exit(1);
}
