/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:15:42 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/24 16:42:03 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long long int nbr, size_t base)
{
	unsigned long long int res;

	res = nbr;
	if (nbr < 0)
	{
		ft_putchar('-');
		res = nbr * -1;
	}
	if (res >= (unsigned long long int)base)
	{
		ft_putnbr_base(res / base, base);
		ft_putnbr_base(res % base, base);
	}
	else
	{
		if (res < 10)
			ft_putchar(res + 48);
		else
			ft_putchar(res - 10 + 97);
	}
}
