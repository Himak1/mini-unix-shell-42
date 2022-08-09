/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 11:25:13 by jhille        #+#    #+#                 */
/*   Updated: 2021/01/23 17:47:00 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	temp;
	int	ret;

	i = 0;
	ret = 0;
	temp = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == 45 || nptr[i] == '+')
	{
		if (nptr[i] == 45)
			temp = 1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ret *= 10;
		ret += nptr[i] - '0';
		i++;
	}
	if (temp == 1)
		return (ret * -1);
	else
		return (ret);
}
