/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <tlepeche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:24:53 by tlepeche          #+#    #+#             */
/*   Updated: 2016/04/21 18:09:37 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int a;

	a = 0;
	if (97 <= c && c <= 122)
		a = (c - 32);
	else
		a = c;
	return (a);
}
