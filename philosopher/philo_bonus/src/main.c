/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:51:51 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/06 14:55:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	philo = init_philo(ac, av);
	i = -1;
	philo->t_start = find_time();
	while (++i < philo->num_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_error("Error => fork", philo);
		if (philo->pid[i] == 0)
		{
			philo->index = i + 1;
			philo->t_meal = find_time();
			philo_start(philo);
			if (pthread_join(philo->check_monitor, NULL))
				ft_error("Error => FAIL join thread", NULL);
			exit_philo_2(philo);
		}
	}
	exit_philo(&philo);
	return (0);
}
