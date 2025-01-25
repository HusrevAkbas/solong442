/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:51:33 by huakbas           #+#    #+#             */
/*   Updated: 2025/01/25 12:29:21 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static int	check_chars(char *nbr, int *p)
{
	int	i;
	int	minus;

	minus = 1;
	i = 0;
	while (nbr[i] == ' ' || (nbr[i] > 8 && nbr[i] && nbr[i] < 14))
	{
		*p += 1;
		i++;
	}
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			minus *= -1;
		*p += 1;
		i++;
	}
	return (minus);
}

int	ft_atoi_base(char *nbr, char *base)
{
	int	b;
	int	res;
	int	i;
	int	is_n;

	if (!nbr || !base)
		return (0);
	i = 0;
	res = 0;
	b = char_in_str(base, '~');
	is_n = check_chars(nbr, &i);
	while (nbr[i])
	{
		if (char_in_str(base, nbr[i]) < b)
			res += res * (b - 1) + char_in_str(base, nbr[i]);
		else
			return (is_n * res);
		i++;
	}
	return (is_n * res);
}
