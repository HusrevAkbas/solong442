/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_zeropadded_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huakbas <huakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:23:46 by huakbas           #+#    #+#             */
/*   Updated: 2024/11/25 15:12:31 by huakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_set_zeropadded_str(t_flags *flags, char *str)
{
	char	*str_new;
	int		i;
	size_t	width;
	size_t	length_str;
	size_t	length_prefix;

	i = 0;
	length_str = ft_strlen(str);
	length_prefix = ft_strlen(flags->prefix);
	width = flags->width;
	if (width < length_str + length_prefix)
		return (ft_set_flagged_str(flags, str));
	str_new = ft_calloc(width + 1, sizeof(char));
	if (str_new == NULL)
		return (NULL);
	ft_memset(str_new, '0', width);
	ft_memcpy(str_new + width - length_str, str, length_str);
	ft_memcpy(str_new, flags->prefix, length_prefix);
	return (str_new);
}
