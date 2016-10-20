/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:24:53 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:28:52 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int a;

	a = 0;
	if (65 <= c && c <= 90)
		a = (c + 32);
	else
		a = c;
	return (a);
}