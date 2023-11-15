/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:37:17 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/13 16:58:13 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	parsing(t_philo *tmp, int ac, char **av)
{
	tmp->num_philos = ft_atoi_modif(av[1]);
	tmp->num_forks = tmp->num_philos;
	tmp->t_die = ft_atoi_modif(av[2]);
	tmp->t_eat = ft_atoi_modif(av[3]);
	tmp->t_sleep = ft_atoi_modif(av[4]);
	if (tmp->t_die < 60 || tmp->t_die < 60 || tmp->t_eat < 60
		|| tmp->t_sleep < 60)
		ft_error("Error Arguments", tmp);
	if (ac == 6)
	{
		tmp->num_eat = ft_atoi_modif(av[5]);
		if (tmp->num_eat < 1)
			ft_error("Error Arguments num_eat negatif", tmp);
	}
	else
		tmp->num_eat = -1;
}

int	ft_atoi_modif(const char *str)
{
	long int	n;
	int			max_int;

	max_int = 2147483647;
	while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v')
		str++;
	n = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		if (n > max_int)
			return (-1);
		str++;
	}
	if (*str != '\0' || n == 0)
		return (-1);
	return ((int)n);
}

t_philo	*init_data(int ac, char **av)
{
	t_philo	*tmp;

	tmp = (t_philo *)malloc(sizeof(t_philo));
	if (!tmp)
		ft_error("Error => Malloc Failed philo", tmp);
	parsing(tmp, ac, av);
	if (tmp->num_philos < 1 || tmp->t_die < 1 || tmp->t_eat < 1
		|| tmp->t_sleep < 1 || ft_check_args(av) != 1)
		ft_error("Error Arguments", tmp);
	if (tmp->t_eat >= tmp->t_sleep)
	{
		if (tmp->num_philos % 2 == 0)
			tmp->t_think = tmp->t_eat - tmp->t_sleep;
		else
			tmp->t_think = (tmp->t_eat + tmp->t_eat) - tmp->t_sleep;
	}
	tmp->died = 0;
	tmp->s_think = 0;
	tmp->s_eat = 0;
	tmp->s_sleep = 0;
	tmp->s_fork1 = 0;
	tmp->s_fork2 = 0;
	return (tmp->num_eat_count = 0, tmp->stop_flag = 0, tmp);
}

void	init_sem(t_philo *philo)
{
	philo->block_printf = sem_open("/block_printf", O_CREAT, 0644, 1);
	philo->block_fork = sem_open("/block_fork", O_CREAT, 0644,
			philo->num_forks);
	philo->block_variable = sem_open("/block_variable", O_CREAT, 0644, 1);
	philo->block_time = sem_open("/block_time", O_CREAT, 0644, 1);
	philo->block_eat = sem_open("/block_eat", O_CREAT, 0644, 1);
	philo->block_sleep_think = sem_open("/block_sleep_think", O_CREAT, 0644, 1);
	if (philo->block_printf <= 0 || philo->block_fork <= 0
		|| philo->block_variable <= 0 || philo->block_eat <= 0
		|| philo->block_time <= 0)
		ft_error("Error semaphore open error", philo);
}

t_philo	*init_philo(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalids numbers of Arguments\n", 31), exit(0), NULL);
	philo = init_data(ac, av);
	philo->pid = (int *)malloc(sizeof(int) * philo->num_forks);
	if (!philo->pid)
		ft_error("Error => malloc pid", philo);
	sem_unlink("/block_printf");
	sem_unlink("/block_fork");
	sem_unlink("/block_variable");
	sem_unlink("/block_time");
	sem_unlink("/block_eat");
	sem_unlink("/block_sleep_think");
	init_sem(philo);
	return (philo);
}
