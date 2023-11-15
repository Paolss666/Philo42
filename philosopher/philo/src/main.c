/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:35:43 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 17:05:24 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

int	main(int ac, char **av)
{
	t_data	table;

	if (!(ac == 5 || ac == 6))
	{
		write(2, "Invalid numbers of Arguments\n", 30);
		return (0);
	}
	if (check_data(ac, av, &table))
		return (0);
	if (init_mutex(&table) != 0)
		return (0);
	run_philo(&table);
	return (0);
}
