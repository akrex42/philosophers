#include "../includes/philo.h"

int		ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			minus;

	i = 0;
	minus = 1;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' ' ||
		   str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * minus);
}