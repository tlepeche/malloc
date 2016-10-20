/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 18:15:42 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/20 18:20:02 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long int nbr, size_t base)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 16)
	{
		ft_putnbr_base(nbr / base, base);
		ft_putnbr_base(nbr % base, base);
	}
	else
	{
		if (nbr < 10)
			ft_putchar(nbr + 48);
		else
			ft_putchar(nbr - 10 + 97);
	}
}
